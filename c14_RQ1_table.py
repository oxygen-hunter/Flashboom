import os
import pandas as pd

def csv_to_latex(csv_path):
        df = pd.read_csv(csv_path)
        # 将 (p, n/N) 数据分开并转换为小数格式
        def process_entry(entry):
            p_str, n_n_str = entry.split(" ")
            p = float(p_str)
            return p, n_n_str.strip("()")

        # 计算各列最大 p 值索引
        p_values = df.iloc[:, 1:].applymap(lambda x: process_entry(x)[0])
        max_indices = p_values.idxmax()

        # 生成 LaTeX 表格代码
        latex_code = "\\begin{table}[h!]\n\\centering\n\\begin{tabular}{|c|" + "c|" * (len(df.columns) - 1) + "}\n\\hline\n"
        latex_code += " & " + " & ".join(df.columns[1:]) + " \\\\\n\n"

        for i, row in df.iterrows():
            row_data = [row['blind_name']]
            for col in df.columns[1:]:
                p, n_N = process_entry(row[col])
                formatted_p = f"\\cellcolor{{blue!10}}{{{p:.4f}}}" if max_indices[col] == i else f"{p:.4f}"
                row_data.append(f"{formatted_p} ({n_N})")
            latex_code += " & ".join(row_data) + " \\\\\n\n"

        latex_code += "\\end{tabular}\n\\end{table}"

        return latex_code

'''
summary by llm
blind_name,yes_yes,yes_no,no_yes,no_no,blind_rate
'''
def RQ1(dataset, enable_percent):
    judge_modes = ['yes_or_no', 'type', 'strict']
    if dataset == 'smartbugs-collection':
        auditors = ['Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi', 'GPT4o']
    elif dataset == 'big-vul-100' or dataset == 'cvefixes-100':
        auditors = ['Mixtral', 'CodeLlama', 'Phi']

    for judge_mode in judge_modes:
        print('judge_mode: ', judge_mode)
        lst = []
        for auditor in auditors:
            self_path = f'results/{dataset}/add_attention_code/{auditor}/top0-100/summary_by_llm/type/{judge_mode}/{auditor}.csv'
            baselines_path = f'results/{dataset}/baselines/summary_by_llm/type/{judge_mode}/{auditor}.csv'
            if auditor == 'GPT4o':
                self_pd = pd.DataFrame(columns=['blind_name','yes_yes','yes_no','no_yes','no_no','blind_rate'])
                self_pd.loc[0] = ['tool', 0,0,0,0,0]
            else:
                self_pd = pd.read_csv(self_path)
                print(f'{dataset} x {auditor} top1: {self_pd.loc[0, 'blind_name']}')
                self_pd.loc[0, 'blind_name'] = 'tool'
            baselines_pd = pd.read_csv(baselines_path)
            top1_line = pd.DataFrame(self_pd.iloc[[0]], columns=self_pd.columns)
            

            if enable_percent:
                # 添加分数计算示例
                top1_line['blind_rate'] = top1_line.apply(lambda row: f'{"{:.4g}".format(row['blind_rate'])} ({row['yes_no']}/{row['yes_yes']+row['yes_no']})', axis=1)
                baselines_pd['blind_rate'] = baselines_pd.apply(lambda row: f'{"{:.4g}".format(row['blind_rate'])} ({row['yes_no']}/{row['yes_yes']+row['yes_no']})', axis=1)

                # 添加分子
                # top1_line['blind_rate'] = top1_line.apply(lambda row: f'{"{:.4g}".format(row['blind_rate'])} ({row['yes_no']})', axis=1)
                # baselines_pd['blind_rate'] = baselines_pd.apply(lambda row: f'{"{:.4g}".format(row['blind_rate'])} ({row['yes_no']})', axis=1)

            combline = pd.concat([top1_line, baselines_pd], ignore_index=True)[['blind_name', 'blind_rate']]
            combline.set_index('blind_name', inplace=True)
            combline.rename(columns={'blind_rate': auditor}, inplace=True)
            # random 1/2/3取最小的然后重命名为random
            combline.loc['random', auditor] = combline.loc[['random1', 'random2', 'random3'], auditor].min()
            combline.drop(index=['random1', 'random2', 'random3'], inplace=True)
            # 调整顺序
            reorder = ['tool', 'random', 'benign_comments', 'benign_rename']
            combline = combline.reindex(reorder)


            lst.append(combline)
            #print(combline)
        summary = pd.concat(lst, axis=1)

        

        os.makedirs(f'results/RQs', exist_ok=True)
        summary_path = f'results/RQs/RQ1-{dataset}-{judge_mode}.csv'
        summary.to_csv(summary_path, float_format='%.4f')
        print('saved to: ', summary_path)

        if enable_percent:
            # 添加分数计算示例
            latex = csv_to_latex(summary_path)
            latex_path = f'results/RQs/RQ1-{dataset}-{judge_mode}.tex'
            with open(latex_path, 'w', encoding='utf-8') as f:
                f.write(latex)
            print('saved to: ', latex_path)

    
enable_percent = True
RQ1('smartbugs-collection', enable_percent)
RQ1('big-vul-100', enable_percent)
RQ1('cvefixes-100', enable_percent)