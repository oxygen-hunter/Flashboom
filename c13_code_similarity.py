import os
import json
from llm_auditor.gte import GteLargeEn
from utils import get_txt_content_as_str
import pandas as pd

'''
results/code_similarity/{dataset}/{flash_name}.csv
     flash_name
case1
case2
...
casen
'''
def code_similarity(model, code1_dir, code2_dir, result_csv_path):
    if os.path.exists(result_csv_path):
        print('code similarity exists: ', result_csv_path)
        return
    print(f'code similarity for code1 {code1_dir}, code2 {code2_dir} ')
    result_dict = {}
    for file1 in os.listdir(code1_dir):
        path1 = os.path.join(code1_dir, file1)
        path2 = os.path.join(code2_dir, file1)
        if os.path.exists(path2):
            str1 = get_txt_content_as_str(path1)
            str2 = get_txt_content_as_str(path2)
            result_dict[file1] = model.similarity([str1, str2])[0]
            print('.', end='', flush=True)
        else:
            result_dict[file1] = -1
    print('\n')
    result_dict = dict(sorted(result_dict.items()))
    
    result_csv = pd.DataFrame.from_dict(result_dict, orient='index', columns=['cosine-similarity'])
    # min max aver
    cos_min = result_csv.loc[:, 'cosine-similarity'].min()
    cos_max = result_csv.loc[:, 'cosine-similarity'].max()
    cos_mean = result_csv.loc[:, 'cosine-similarity'].mean()
    result_csv.loc['min'] = [cos_min]
    result_csv.loc['max'] = [cos_max]
    result_csv.loc['mean'] = [cos_mean]

    # 使用 applymap 和格式化保留四位小数
    result_csv = result_csv.applymap(lambda x: f"{x:.4f}" if isinstance(x, float) else x)

    result_csv.to_csv(result_csv_path, float_format='%.4f')
    print('code similarity saved to: ', result_csv_path)


def batch_code_similarity(dataset, auditor, flash_name):
    match dataset:
        case 'smartbugs-collection': ext = '.sol'
        case 'big-vul-100': ext = '.cpp'
        case 'cvefixes-100': ext = '.py'

    code_dir = f'data/{dataset}/code'
    flash_code_dir = f'data/{dataset}/add_attention_code/{auditor}/top0-100/{flash_name}'
    if not os.path.exists(flash_code_dir):
        print('flash_code dir not found: ', flash_code_dir)
    result_csv_dir = f'results/code_similarity/{dataset}'
    os.makedirs(result_csv_dir, exist_ok=True)
    result_csv_path = f'results/code_similarity/{dataset}/{flash_name}.csv'
    code_similarity(model=model, code1_dir=code_dir, code2_dir=flash_code_dir, result_csv_path=result_csv_path)


def top1_name_of_each_model(model_name, dataset, judge_mode):
    csv_path = f'results/{dataset}/add_attention_code/{model_name}/top0-100/summary_by_llm/type/{judge_mode}/{model_name}.csv'
    if os.path.exists(csv_path):
        df = pd.read_csv(csv_path)
        return df['blind_name'][0]
    else:
        return None

def batch_top1_name_code_similarity(dataset):
    # if dataset == 'smartbugs-collection':
    #     auditors = ['Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi']
    # elif dataset == 'big-vul-100' or dataset == 'cvefixes-100':
    #     auditors = ['Mixtral', 'CodeLlama', 'Phi']
    auditors = ['Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi']
    for auditor in auditors:
        j1_name = top1_name_of_each_model(model_name=auditor, dataset=dataset, judge_mode='yes_or_no')
        j2_name = top1_name_of_each_model(model_name=auditor, dataset=dataset, judge_mode='type')
        batch_code_similarity(dataset=dataset, auditor=auditor, flash_name=j1_name)
        batch_code_similarity(dataset=dataset, auditor=auditor, flash_name=j2_name)

def collect_result():
    result_dict1 = {}
    result_dict2 = {}
    datasets = ['smartbugs-collection', 'big-vul-100', 'cvefixes-100']
    auditors = ['Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi']
    for auditor in auditors:
        result_dict1[auditor] = {}
        result_dict2[auditor] = {}
        for dataset in datasets:
    
            j1_name = top1_name_of_each_model(model_name=auditor, dataset=dataset, judge_mode='yes_or_no')
            j2_name = top1_name_of_each_model(model_name=auditor, dataset=dataset, judge_mode='type')
            
            def handle_one(result_dict, j_name, dataset):
                result_csv_path = f'results/code_similarity/{dataset}/{j_name}.csv'
                if j_name:
                    df = pd.read_csv(result_csv_path, index_col=0)
                    #print(df.index)
                    min = df.loc['min', 'cosine-similarity']
                    max = df.loc['max', 'cosine-similarity']
                    mean = df.loc['mean', 'cosine-similarity']
                else:
                    min = max = mean = '-'
                result_dict[auditor][dataset] = {
                    'min': min,
                    'max': max,
                    'mean': mean,
                }
                return result_dict
            result_dict1 = handle_one(result_dict1, j_name=j1_name, dataset=dataset)
            result_dict2 = handle_one(result_dict2, j_name=j2_name, dataset=dataset)
    
    def dict2pd(d, csv_path):
        d = {(k, sk):sv for k, v in d.items() for sk, sv in v.items()}
        df = pd.DataFrame.from_dict(d, orient='index')
        # 使用 unstack 将第二级索引展开为列
        df_unstacked = df.unstack(level=1)

        # 将多层列索引展平，形成一个扁平的列名
        df_unstacked.columns = [f"{col[1]}_{col[0]}" for col in df_unstacked.columns]
        ordered_columns = [
            'smartbugs-collection_min', 'smartbugs-collection_max', 'smartbugs-collection_mean',
            'big-vul-100_min', 'big-vul-100_max', 'big-vul-100_mean',
            'cvefixes-100_min', 'cvefixes-100_max', 'cvefixes-100_mean'
        ]

        # 重新排序列
        df_unstacked = df_unstacked[ordered_columns]

        # 指定自定义的索引顺序
        desired_order = ['Mixtral', 'CodeLlama', 'Phi', 'MixtralExpert', 'Gemma', ]
        df_unstacked.index = pd.CategoricalIndex(df_unstacked.index, categories=desired_order, ordered=True)

        # 按自定义顺序排序
        df_unstacked = df_unstacked.sort_index()

        df_unstacked.to_csv(csv_path)
        print(df_unstacked)
    dict2pd(result_dict1, 'results/RQs/RQ4-yes_or_no.csv')
    dict2pd(result_dict2, 'results/RQs/RQ4-type.csv')


        
model = GteLargeEn()
batch_top1_name_code_similarity(dataset='smartbugs-collection')
batch_top1_name_code_similarity(dataset='big-vul-100')
batch_top1_name_code_similarity(dataset='cvefixes-100')
collect_result()