'''
input:
--working_dir
    --evaluate
        --Mixtral
            --same_rag.csv
            --xx.csv
        --Phi
        --..
    --summary_by_llm/{llm}.csv
    --summary_by_method/{method}.csv

steps:
1. read 'same_rag' column and other columns
yes_yes = same ==3/4 and other == 3/4
yes_no = same==3/4 and other == 1/2
no_yes : same==1/2 and other == 3/4
no_no : same==1/2 and other == 1/2
2. collect yes_yes and yes_no by method

'''

import json
import shutil
import pandas as pd
import os

'''
eval report (evaluate/{eval_mode}/{auditor}/{method}.csv)
case_id, vuln_type, audit_report, gt, eval_score, eval_input_token_num, eval_output_token_num, eval_inerence_time

summary by llm (summary_by_llm/{eval_mode}/{auditor}.csv)
blind_name, yes_yes, yes_no, no_yes, no_no, blind_rate
'''
def summary_by_llm(eval_csv_dir, output_path, judge_mode):

    yes_yes_count = {}
    yes_no_count = {}
    no_yes_count = {}
    no_no_count = {}

    # same_rag
    same_rag_csv_path = os.path.join(eval_csv_dir, 'same_rag.csv')
    if not os.path.exists(same_rag_csv_path):
        raise ValueError('same_rag not found in ', eval_csv_dir)
    same_rag_df = pd.read_csv(same_rag_csv_path)
    
    # other method
    for file in os.listdir(eval_csv_dir):
        if file.endswith('.csv') and file != 'same_rag.csv':
            file_path = os.path.join(eval_csv_dir, file)
            method = file.split('.csv')[0]
            yes_yes_count[method] = 0
            yes_no_count[method] = 0
            no_yes_count[method] = 0
            no_no_count[method] = 0

            other_df = pd.read_csv(file_path)

            for index, row in other_df.iterrows():
                same_rag_cell = int(same_rag_df.at[index, 'eval_score'])
                other_cell = int(other_df.at[index, 'eval_score'])
                if judge_mode == 'yes_or_no': # consider 2,3,4 downgrade to 1
                    first_yes = same_rag_cell == 3 or same_rag_cell == 4 or same_rag_cell == 2
                    second_yes = other_cell == 3 or other_cell == 4 or other_cell == 2 
                elif judge_mode == 'type': # consider 3,4 downgrade to 1,2
                    first_yes = same_rag_cell == 3 or same_rag_cell == 4
                    second_yes = other_cell == 3 or other_cell == 4 
                elif judge_mode == 'strict': # consider 3,4 downgradge to 1
                    first_yes = same_rag_cell == 3 or same_rag_cell == 4
                    second_yes = other_cell == 3 or other_cell == 4 or other_cell == 2 
                yes_yes_count[method] += 1 if first_yes and second_yes else 0
                yes_no_count[method] += 1 if first_yes and not second_yes else 0
                no_yes_count[method] += 1 if not first_yes and second_yes else 0
                no_no_count[method] += 1 if not first_yes and not second_yes else 0



    blind_rate = {method: yes_no_count[method]/(yes_yes_count[method]+yes_no_count[method]) if (yes_yes_count[method]+yes_no_count[method]) > 0 else 0 for method in yes_yes_count}

    summary = {
        'yes_yes': yes_yes_count,
        'yes_no': yes_no_count,
        'no_yes': no_yes_count,
        'no_no': no_no_count,
        'blind_rate': blind_rate
    }
    summary = pd.DataFrame(summary)
    # add blind_name as header to index
    summary = summary.reset_index().rename(columns={'index': 'blind_name'})
    
    # sort by blind_rate
    summary = summary.sort_values(by=['blind_rate', 'blind_name'], ascending=[False, True])
    summary.to_csv(output_path, index=False)
    print('summary by llm saved to: ', output_path)


def summary_by_method(summary_by_llm_dir, summary_by_method_dir):
    # 读取文件夹中的所有CSV文件
    csv_files = [f for f in os.listdir(summary_by_llm_dir) if f.endswith('.csv')]

    # 初始化一个字典，用于存储不同第一个单元格值的行
    grouped_data = {}

    # 遍历每个CSV文件
    for csv_file in csv_files:
        file_path = os.path.join(summary_by_llm_dir, csv_file)
        df = pd.read_csv(file_path)
        
        # 遍历每一行
        for _, row in df.iterrows():
            key = row.iloc[0]  # 获取第一个单元格的值
            
            # 如果该值不在字典中，初始化为一个空列表
            if key not in grouped_data:
                grouped_data[key] = []
            
            # 将该行添加到对应的键值下
            row.iloc[0] = csv_file.split('.csv')[0]
            grouped_data[key].append(row)

    # 将每个组的数据保存到不同的CSV文件中
    for key, rows in grouped_data.items():
        output_path = os.path.join(summary_by_method_dir, f'{key}.csv')
        
        # 将列表转为DataFrame
        output_df = pd.DataFrame(rows)

        # 删3/4列
        # output_df = output_df.drop(output_df.columns[[3,4]], axis=1)
        # 新增一列rate
        output_df['blind_rate'] = output_df.apply(lambda row: row.iloc[2] / (row.iloc[1] + row.iloc[2]) if (row.iloc[1] + row.iloc[2]) != 0 else 0, axis=1)
        
        # 保存到CSV文件
        output_df.to_csv(output_path, index=False)

        print(f'summary by method saved to: ', output_path)


def mean_of_blind_rate(summary_by_llm_dir, output_path):
    mean_dict = {}
    for file in os.listdir(summary_by_llm_dir):
        if file.endswith('.csv'):
            model_name = file.split('.csv')[0]
            file_path = os.path.join(summary_by_llm_dir, file)
            df = pd.read_csv(file_path)
            mean = df['blind_rate'].mean()
            mean_dict[model_name] = mean
    
    with open(output_path, 'w', encoding='utf-8') as f:
        json.dump(mean_dict, f, indent=2)


# def test_summary_by_llm():
#     eval_csv_path = 'results/vuln-10/add_attention_code/Mixtral/Mixtral_eval.test.csv'
#     output_path = 'results/vuln-10/add_attention_code/Mixtral/summary_by_llm/Mixtral.test.csv'
#     summary_by_llm(eval_csv_path, output_path)


# def test_summary_by_method():
#     working_dir = 'results/vuln-10/add_attention_code/Mixtral'
#     folder_path = f'{working_dir}/summary_by_llm'
#     output_folder = f'{working_dir}/summary_by_method'
#     summary_by_method(folder_path, output_folder)


def batch_count_blind(working_dir, evaluate_modes, judge_modes):
    # working_dir = 'results/add_attention_code/Mixtral/top0-100'
    # evaluate_mode = 'type'
    if 'all' in evaluate_modes:
        evaluate_modes = ['yes_or_no', 'type', 'reason']
    if 'all' in judge_modes:
        judge_modes = ['yes_or_no', 'type', "strict"]
    
    for evaluate_mode in evaluate_modes:
        eval_dir = os.path.join(working_dir, 'evaluate', evaluate_mode)
        if not os.path.exists(eval_dir):
            raise ValueError('eval_dir no found: ', eval_dir)
            continue
        for judge_mode in judge_modes:
            # summary of each llm
            summary_by_llm_dir = os.path.join(working_dir, 'summary_by_llm', evaluate_mode, judge_mode)
            if os.path.exists(summary_by_llm_dir):
                shutil.rmtree(summary_by_llm_dir)
            os.makedirs(summary_by_llm_dir)
            for auditor in sorted(os.listdir(eval_dir)):
                eval_csv_dir = os.path.join(eval_dir, auditor)
                summary_by_llm_path = os.path.join(summary_by_llm_dir, f'{auditor}.csv')
                summary_by_llm(eval_csv_dir=eval_csv_dir, output_path=summary_by_llm_path, judge_mode=judge_mode)
            # compute mean of each llm
            mean_path = os.path.join(summary_by_llm_dir, 'mean.json')
            mean_of_blind_rate(summary_by_llm_dir, mean_path)
            
            # summary of each method
            summary_by_method_dir = os.path.join(working_dir, 'summary_by_method', evaluate_mode, judge_mode)
            if os.path.exists(summary_by_method_dir):
                shutil.rmtree(summary_by_method_dir)
            os.makedirs(summary_by_method_dir)
            summary_by_method(summary_by_llm_dir, summary_by_method_dir)
