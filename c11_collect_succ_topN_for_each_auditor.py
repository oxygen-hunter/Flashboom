import os
import shutil

import pandas as pd

def topN_names_in_csv(csv_path, N)->list:
    df = pd.read_csv(csv_path)
    return list(df['blind_name'][:N])

def collect_topN_names_to_todo_code_dir(model_name, N, dataset, judge_mode, do_copy=False):
    csv_path = f'results/{dataset}/add_attention_code/{model_name}/top0-100/summary_by_llm/type/{judge_mode}/{model_name}.csv'
    todo_code_par_dir = f'data/{dataset}/top{N}_succ_of_whitebox_{judge_mode}/{model_name}'
    names = topN_names_in_csv(csv_path, N)
    print(f'auditor: {model_name}, dataset: {dataset}, judge_mode: {judge_mode}, top{N}: {names}')

    if do_copy:
        if os.path.exists(todo_code_par_dir):
            shutil.rmtree(todo_code_par_dir)
        os.makedirs(todo_code_par_dir, exist_ok=True)
        for name in names:
            src_dir = f'data/{dataset}/add_attention_code/{model_name}/top0-100/{name}'
            dst_dir = f'{todo_code_par_dir}/{name}'
            shutil.copytree(src_dir, dst_dir)
            print(f'copied: src: {src_dir}, dst: {dst_dir}')


def topN_names_succ_rate_on_other_models(src_models, dst_models, N, dataset, judge_mode):
    summary = {}
    for src_m in src_models:
        src_topN_csv_path = f'results/{dataset}/add_attention_code/{src_m}/top0-100/summary_by_llm/type/{judge_mode}/{src_m}.csv'
        topN_names = topN_names_in_csv(src_topN_csv_path, 3)
        summary[src_m] = {}
        for i, name in enumerate(topN_names):
            topname = f'top{i+1}'
            summary[src_m][topname] = {}
            for dst_m in dst_models:
                dst_succ_csv = f'results/{dataset}/top{N}_succ_of_whitebox_{judge_mode}/{src_m}/summary_by_method/type/{judge_mode}/{name}.csv'
                df = pd.read_csv(dst_succ_csv)
                dst_succ_rate = -1
                for index, row in df.iterrows():
                    if row.loc['blind_name'] == dst_m:
                        dst_succ_rate = row.loc['blind_rate']
                        break
                if dst_succ_rate == -1:
                    raise ValueError('dst model not found, ', name, dst_succ_csv)
                else:
                    summary[src_m][topname][dst_m] = dst_succ_rate

    summary_df = pd.DataFrame.from_dict({(key, subkey):values for key, subdict in summary.items() for subkey, values in subdict.items()}, orient='columns')
    print(summary_df)
    summary_csv_path = f'results/RQs/RQ2-top{N}succ_results_summary.{dataset}.{judge_mode}.csv'
    summary_df.to_csv(summary_csv_path, float_format='%.4f')
    print('saved to: ', summary_csv_path)

def batch_collect_source(N, dataset, do_copy):
    if dataset == 'smartbugs-collection':
        models = ['Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi']
    elif dataset == 'big-vul-100' or dataset == 'cvefixes-100':
        models = ['Mixtral', 'CodeLlama', 'Phi']
    for model in models:
        collect_topN_names_to_todo_code_dir(model_name=model, N=N, dataset=dataset, judge_mode='yes_or_no', do_copy=do_copy)
        collect_topN_names_to_todo_code_dir(model_name=model, N=N, dataset=dataset, judge_mode='type', do_copy=do_copy)
        collect_topN_names_to_todo_code_dir(model_name=model, N=N, dataset=dataset, judge_mode='strict', do_copy=do_copy)

def batch_summary_results():
    srcs = ['Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi']
    dsts = ['Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi', 'GPT4o']
    topN_names_succ_rate_on_other_models(src_models=srcs, dst_models=dsts, N=3, dataset='smartbugs-collection', judge_mode='yes_or_no')
    topN_names_succ_rate_on_other_models(src_models=srcs, dst_models=dsts, N=3, dataset='smartbugs-collection', judge_mode='type')
    topN_names_succ_rate_on_other_models(src_models=srcs, dst_models=dsts, N=3, dataset='smartbugs-collection', judge_mode='strict')

#batch_collect_source(N=3, dataset='smartbugs-collection', do_copy=True)
#batch_collect_source(N=3, dataset='smartbugs-collection', do_copy=True)
# batch_collect_source(N=1, dataset='smartbugs-collection', do_copy=False)
# batch_collect_source(N=1, dataset='big-vul-100', do_copy=False)
# batch_collect_source(N=1, dataset='cvefixes-100', do_copy=False)

batch_summary_results()