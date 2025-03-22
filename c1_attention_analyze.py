import json
import re
import time

import torch



from utils import *
from utils_model import init_model

'''
contractN
    - 1001.sol
    - 1002.sol

output_dir
    - 1001.csv
    - 1001.png
    - ...
'''
def compute_attention_for_sol_files(sol_dir, output_dir, model):
    todo_ids = [int(f.split('.sol')[0]) for f in os.listdir(sol_dir)]
    min_todo_id = min(todo_ids) if len(todo_ids) > 0 else -1
    max_todo_id = max(todo_ids) if len(todo_ids) > 0 else -1

    succ_ids = [int(f.split('.csv')[0]) if f.endswith('.csv') else -1 for f in os.listdir(output_dir)]
    max_succ_id = max(succ_ids)+1 if len(succ_ids) > 0 else min_todo_id

    print(f'compute attention for id range {max_succ_id}-{max_todo_id}')

    for id in range(max_succ_id, max_todo_id+1):
        sol_file_path = os.path.join(sol_dir, f'{id}.sol')
        user_prompt = get_txt_content_as_str(sol_file_path)
        os.makedirs(output_dir, exist_ok=True)
        output_path_prefix = os.path.join(output_dir, f'{id}')
        
        print('.', end='', flush=True)
        try:
            time_used = model.draw_attention(user_prompt, output_path_prefix)
            #print('succ ', output_path)
        except Exception as e:
            #print(e)
            #print('fail ', file_path)
            print('o', end='', flush=True)

'''
for each source ends with {file_format} in {source_dir}, use {model} to compute its linewise attention .csv .png, to {output_dir}
cache file in {output_dir}/{finish.json}, three status: succ/fail/todo
'''
def compute_attention_for_source_files(source_dir, file_format, output_dir, model):
    print(f'compute attention, source_dir: {source_dir}, output_dir: {output_dir}')
    finish_status_path = os.path.join(output_dir, 'finish.json')
    if os.path.exists(finish_status_path):
        with open(finish_status_path, 'r', encoding='utf-8') as f:
            finish = json.load(f)
    else:
        finish = {}

    os.makedirs(output_dir, exist_ok=True)
    if not os.path.exists(source_dir):
        #raise ValueError('source dir not found: ', source_dir)
        print('source dir not found: ', source_dir)
        return
    for file in os.listdir(source_dir):
        #if file in finish and (finish[file] == 'succ' or finish[file] == 'fail'):
        if file in finish and (finish[file] == 'succ'):
            continue
        finish[file] = 'todo'
        with open(finish_status_path, 'w', encoding='utf-8') as f:
            json.dump(finish, f, indent=2)
        source_file_path = os.path.join(source_dir, file)
        user_prompt = get_txt_content_as_str(source_file_path)
        
        output_path_prefix = os.path.join(output_dir, file.split(file_format)[0])
        
        print('.', end='', flush=True)
        finish[file] = 'succ'
        with open(finish_status_path, 'w', encoding='utf-8') as f:
            json.dump(finish, f, indent=2)
        try:
            time_used = model.draw_attention(user_prompt, output_path_prefix)
            #print('succ ', output_path)
        except Exception as e:
            #print(e)
            #print('fail ', file_path)
            print('o', end='', flush=True)
            finish[file] = 'fail'
            with open(finish_status_path, 'w', encoding='utf-8') as f:
                json.dump(finish, f, indent=2)
    print('\n')





def batch_attention_analyze(analyzers, dataset, flash_json_path, flash_code_par_dir, todo_code_par_dir):
    if 'all' in analyzers:
        analyzers = ['Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi']
    for model_name in analyzers:
        model = init_model(model_name, max_new_tokens=500)
        print('analyzer: ', model.__class__.__name__)

        if dataset == 'messiq_dataset':
            parent_dir = 'data/{dataset}'
            file_format = '.sol'
            output_dir = f'results/attention_view_vmax1/{model.__class__.__name__}/{dataset}'
            compute_attention_for_source_files(source_dir=parent_dir, file_format=file_format, output_dir=output_dir, model=model)
            torch.cuda.empty_cache()
        elif dataset == 'leetcode_cpp':
            parent_dir = f'data/{dataset}'
            file_format = '.cpp'
            output_dir = f'results/attention_view_vmax1/{model.__class__.__name__}/{dataset}'
            compute_attention_for_source_files(source_dir=parent_dir, file_format=file_format, output_dir=output_dir, model=model)
        elif dataset == 'leetcode_python':
            parent_dir = f'data/{dataset}'
            file_format = '.py'
            output_dir = f'results/attention_view_vmax1/{model.__class__.__name__}/{dataset}'
            compute_attention_for_source_files(source_dir=parent_dir, file_format=file_format, output_dir=output_dir, model=model)
        elif dataset == 'smartbugs-collection':
            parent_dir = f'data/{dataset}/code'
            file_format = '.sol'
            output_dir = f'results/attention_view_vmax1/{model.__class__.__name__}/{dataset}'
            compute_attention_for_source_files(source_dir=parent_dir, file_format=file_format, output_dir=output_dir, model=model)
            pass
        elif dataset == 'big-vul-100':
            parent_dir = f'data/{dataset}/code'
            file_format = '.cpp'
            output_dir = f'results/attention_view_vmax1/{model.__class__.__name__}/{dataset}'
            compute_attention_for_source_files(source_dir=parent_dir, file_format=file_format, output_dir=output_dir, model=model)
            pass
        elif dataset == 'cvefixes-100':
            parent_dir = f'data/{dataset}/code'
            file_format = '.py'
            output_dir = f'results/attention_view_vmax1/{model.__class__.__name__}/{dataset}'
            compute_attention_for_source_files(source_dir=parent_dir, file_format=file_format, output_dir=output_dir, model=model)
            pass
        elif dataset == 'smartbugs':
            parent_dir = f'data/{dataset}/code'
            file_format = '.sol'
            output_dir = f'results/attention_view_vmax1/{model.__class__.__name__}/{dataset}'
            compute_attention_for_source_files(source_dir=parent_dir, file_format=file_format, output_dir=output_dir, model=model)
            pass
        elif dataset == 'cppbugs-20':
            parent_dir = f'data/{dataset}/code'
            file_format = '.cpp'
            output_dir = f'results/attention_view_vmax1/{model.__class__.__name__}/{dataset}'
            compute_attention_for_source_files(source_dir=parent_dir, file_format=file_format, output_dir=output_dir, model=model)
            pass

        # compute attention for code inserted by blind module
        if flash_json_path: # function_selection/leetcode_cpp/CodeLlama/sum/100/summary.json
            if not os.path.exists(flash_json_path):
                raise ValueError('flash json not found: ', flash_json_path)
            with open(flash_json_path, 'r', encoding='utf-8') as f:
                flashs_dict = json.load(f) 
                # {
                # "function_selection/messiq_dataset/Mixtral/sum/all/9880-Authority.canCall.sol": 208.34135341644287,
                # "function_selection/leetcode_python/Phi/sum/all/subarrays-distinct-element-sum-of-squares-ii-Solution2.sumCounts.py": 1282.128873884678,
            for key in flashs_dict:
                flash_name = os.path.basename(key).split(file_format)[0] # 9880-Authority.canCall.sol
                #flash_code_par_dir: data/smartbugs-collection/add_attention_code/Mixtral/top0-100/261-EBU.transfer
                flash_code_dir = os.path.join(flash_code_par_dir, flash_name)
                flash_output_dir = f'results/attention_view_vmax1/{model.__class__.__name__}/{dataset+'-flash'}/{flash_name}'
                compute_attention_for_source_files(source_dir=flash_code_dir, file_format=file_format, output_dir=flash_output_dir, model=model)
        if todo_code_par_dir:
            for flash_name in os.listdir(todo_code_par_dir):
                flash_code_dir = os.path.join(todo_code_par_dir, flash_name)
                flash_output_dir = f'results/attention_view_vmax1/{model.__class__.__name__}/{dataset+'-flash'}/{flash_name}'
                compute_attention_for_source_files(source_dir=flash_code_dir, file_format=file_format, output_dir=flash_output_dir, model=model)
    
    print('finish')