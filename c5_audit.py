import json
import re
import shutil
import time

import os
import csv
import torch

import pandas as pd

# from llm_auditor.gemma_2b import Gemma
# from llm_auditor.mixtral_7b import Mixtral
# from llm_auditor.mixtral_8x7b import MixtralExpert
# from llm_auditor.codellama_7b import CodeLlama
# from llm_auditor.phi3_medium import Phi
# from llm_auditor.gpt4 import GPT4o

from utils import get_txt_content_as_str
from utils_model import init_model


'''
audit all todocode in {todocode_dir} and save the audit result to ..{analyzer}/{require}/audit_result_{audit_mode}/{model}/{method}.csv

case-id, vuln_type, audit_report, input_token_num, output_token_num, inference_time
'''
def process_files_without_prompt(model, model_name, dataset, todo_code_dir, result_csv_path, audit_mode):

    redo_list = [
    ]
    

    if os.path.exists(result_csv_path) and not result_csv_path in redo_list:
        print('audit result exists: ', result_csv_path)
        return
    
    cache_analyzers = ['Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi', 'GPT4o']
    for analyzer in cache_analyzers:
        cached_paths = [
            f'results/{dataset}/add_attention_code/{analyzer}/top0-100/audit_result_{audit_mode}/{model_name}/{os.path.basename(result_csv_path)}',
            f'results/{dataset}/top3_succ_of_whitebox_type/{analyzer}/audit_result_{audit_mode}/{model_name}/{os.path.basename(result_csv_path)}',
            f'results/{dataset}/top3_succ_of_whitebox_yes_or_no/{analyzer}/audit_result_{audit_mode}/{model_name}/{os.path.basename(result_csv_path)}',
        ]
        for cached_path in cached_paths:
            #print(cached_path)
            if os.path.exists(cached_path) and cached_path != result_csv_path and not result_csv_path in redo_list:
                shutil.copy(cached_path, result_csv_path)
                print('audit result cached: ', cached_path)
                return

    print('auditing: ', todo_code_dir)
    result_dict = {}
    for filename in os.listdir(todo_code_dir):
        if filename.endswith(('.sol', '.cpp', '.py')):
            # {N}_{vuln_type}.sol
            # {index}_{vuln_type}.cpp/.py
            ext = '.'+filename.split('.')[-1]
            key_parts = filename.split('_')
            if len(key_parts) >= 2:
                key = f'{key_parts[0]}'
                vuln_type = f'{' '.join(key_parts[1:])}'
                vuln_type = vuln_type.split(ext)[0]
                todo_code_path = os.path.join(todo_code_dir, filename)
                todo_code = get_txt_content_as_str(todo_code_path)

                # 调用audit函数并存储结果
                (
                    result,
                    input_token_num,
                    output_token_num,
                    inference_time,
                    # queried_text,
                    # score,
                ) = model.audit(audit_mode=audit_mode, todo_code=todo_code, dataset=dataset, todo_filename=filename)
                result_dict[key] = {
                    'case_id': key,
                    'vuln_type': vuln_type,
                    'audit_report': result,
                    'input_token_num': input_token_num,
                    'output_token_num': output_token_num,
                    'inference_time': inference_time
                }
                print('.', end='', flush=True)
            else:
                print(f"Filename {filename} does not match expected format")
    
    # sort by key (int)
    result_dict = dict(sorted(result_dict.items(), key=lambda item:int(item[0])))
    df = pd.DataFrame.from_dict(result_dict, orient='index')
    df.to_csv(result_csv_path, index=False)
    print('\n')
    print('audit result saved to: ', result_csv_path)


def batch_audit(auditors, dataset, todo_code_par_dir, audit_output_dir, audit_mode):
    if 'all' in auditors:
        auditors = ['Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi', 'GPT4o']
    for model_name in auditors:
        if model_name == 'Phi':
            use_flash_attn = True
        else:
            use_flash_attn = False
        model = init_model(model_name=model_name, max_new_tokens=300, use_flash_attn=use_flash_attn)
        if model == None:
            raise ValueError('unknown model: ', model_name)
        #model = None
        print('auditor: ', model_name)

        # todo code (all under todo_code_par_dir)
        if os.path.exists(todo_code_par_dir):
            todo_code_method_list = os.listdir(todo_code_par_dir)
        else:
            print('todo_code_par_dir not found: ', todo_code_par_dir)
            todo_code_method_list = []
        result_csv_dir = os.path.join(audit_output_dir, f'audit_result_{audit_mode}', model_name)
        os.makedirs(result_csv_dir, exist_ok=True)

        # same_rag
        same_rag_todo_code_dir = f'data/{dataset}/code'
        result_csv_path= os.path.join(result_csv_dir, 'same_rag.csv')
        process_files_without_prompt(
            model=model,
            model_name=model_name,
            dataset=dataset,
            todo_code_dir=same_rag_todo_code_dir,
            result_csv_path=result_csv_path,
            audit_mode=audit_mode
            )
        
        
        # others
        for method in todo_code_method_list:
            if method == 'code': continue
            todo_code_dir = os.path.join(todo_code_par_dir, method)
            result_csv_path= os.path.join(result_csv_dir, method+'.csv')
            process_files_without_prompt(
                model=model,
                model_name=model_name,
                dataset=dataset,
                todo_code_dir=todo_code_dir,
                result_csv_path=result_csv_path,
                audit_mode=audit_mode
                )
            
        # clean
        torch.cuda.empty_cache()
    print('finished')


def test_auditor():
    todo_code_path = 'data/vuln-10/code/1_re_entrancy.sol'
    todo_code = get_txt_content_as_str(todo_code_path)
    todo_filename = os.path.basename(todo_code_path)

    model = Phi()
    (results, input_token_length, output_token_length, inference_time) = model.audit(todo_code=todo_code, todo_filename=todo_filename)
    print(results, input_token_length, output_token_length, inference_time)

    model = GPT4o()
    (results, input_token_length, output_token_length, inference_time) = model.audit(todo_code=todo_code, todo_filename=todo_filename)
    print(results, input_token_length, output_token_length, inference_time)


def test_auditor_more():
    model = Gemma()
    todo_code_dir = 'data/vuln-10/code'
    for file in os.listdir(todo_code_dir):
        if file.endswith('.sol'):
            todo_code_path = os.path.join(todo_code_dir, file)
            todo_code = get_txt_content_as_str(todo_code_path)
            todo_filename = os.path.basename(todo_code_path)

            (results, input_token_length, output_token_length, inference_time) = model.audit(todo_code=todo_code, todo_filename=todo_filename)
            print(results, input_token_length, output_token_length, inference_time)
