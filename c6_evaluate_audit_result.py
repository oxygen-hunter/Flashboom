import json
import shutil
import pandas as pd
import os
from utils import get_txt_content_as_str
from utils_model import init_model
from llm_auditor.gpt4 import GPT4o
import ast
import pandas as pd

from llm_evaluator.evaluate_score_1_to_4 import evaluate_vuln_report_1_to_4
from llm_evaluator.evaluate_score_1_to_2 import evaluate_vuln_report_1_to_2    


def index_gt_description_as_str(dataset, case_id:int)->str:
    gt_dir = f'data/{dataset}/explanation' # TODO
    if os.path.exists(gt_dir):
        for candidate in os.listdir(gt_dir):
            candidate_id = int(candidate.split('_')[0])
            if case_id == candidate_id:
                gt_path = os.path.join(gt_dir, candidate)
                return get_txt_content_as_str(gt_path)

    vuln_detail_csv_path = f'data/{dataset}/code/vuln_detail.csv'
    if os.path.exists(vuln_detail_csv_path):
        df = pd.read_csv(vuln_detail_csv_path)
        for index, row in df.iterrows():
            candidate_id = int(row['file_name'].split('_')[0])
            if case_id == candidate_id:
                gt = row['explanation']
                return gt

    raise ValueError('gt description not found: ', dataset, case_id)


'''
audit report (audit_result/{auditor}/{method}.csv)
case_id, vuln_type, audit_report, input_token_num, output_token_num, inference_time

eval report (evaluate/{eval_mode}/{auditor}/{method}.csv)
case_id, vuln_type, audit_report, gt, eval_score, eval_input_token_num, eval_output_token_num, eval_inference_time
'''
def evaluate_audit_result_single_csv(model, dataset, auditor_name, audit_result_path, eval_path, eval_mode):

    redo_list = [
    ]

    if os.path.exists(eval_path) and not eval_path in redo_list:
        print('eval result exists: ', eval_path)
        return
    cache_analyzers = ['Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi', 'GPT4o']
    for analyzer in cache_analyzers:
        cached_paths = [
            f'results/{dataset}/add_attention_code/{analyzer}/top0-100/evaluate/{eval_mode}/{auditor_name}/{os.path.basename(eval_path)}',
            f'results/{dataset}/top3_succ_of_whitebox_type/{analyzer}/evaluate/{eval_mode}/{auditor_name}/{os.path.basename(eval_path)}',
            f'results/{dataset}/top3_succ_of_whitebox_yes_or_no/{analyzer}/evaluate/{eval_mode}/{auditor_name}/{os.path.basename(eval_path)}',
        ]
        for cached_path in cached_paths:
            #print(cached_path)
            if os.path.exists(cached_path) and cached_path != eval_path and not eval_path in redo_list:
                shutil.copy(cached_path, eval_path)
                print('eval result cached: ', cached_path)
                return

    print('evaluating: ', audit_result_path)
    audit_df = pd.read_csv(audit_result_path)
    eval_df = audit_df[['case_id', 'vuln_type', 'audit_report']].copy()
    eval_method = None
    match eval_mode:
        case 'yes_or_no': 
            eval_method = None
        case 'type': 
            eval_method = evaluate_vuln_report_1_to_4
        case 'reason': 
            eval_method = None
    
    for index, row in audit_df.iterrows():
        case_id = int(row.loc['case_id'])
        case_vuln_type = str(row.loc['vuln_type'])
        vuln_explan = index_gt_description_as_str(dataset, case_id)
        # TODO
        match dataset:
            case 'smartbugs-collection': correct_report = case_vuln_type
            case 'smartbugs': correct_report = case_vuln_type
            case 'big-vul-100': correct_report = vuln_explan
            case 'cvefixes-100': correct_report = vuln_explan
            case 'cppbugs-20': correct_report = case_vuln_type

        predicted_report = str(row.loc['audit_report'])
        eval_score, runtime_info = eval_method(model, predicted_report=predicted_report, correct_report=correct_report)
        eval_df.at[index, f'gt'] = correct_report
        eval_df.at[index, f'eval_score'] = eval_score
        for info in runtime_info:
            eval_df.at[index, f'eval_{info}'] = runtime_info[info]
        print('.', end='', flush=True)
    print('\n')

    eval_df.to_csv(eval_path, index=False)
    print('eval result saved to: ', eval_path)


'''
- working_dir
-- audit_result
    -- Mixtral
        -- xx.csv
    -- Phi
    -- ...
-- evaluate
    -- yes_or_no
    -- type
    -- reason
-- ..
'''
def batch_eval(evaluator, dataset, auditors, working_dir, evaluate_mode):
    model = init_model(evaluator, max_new_tokens=100)
    audit_dir = os.path.join(working_dir, 'audit_result_rag')
    evaluate_dir = os.path.join(working_dir, 'evaluate', evaluate_mode)

    if 'all' in auditors:
        auditors = ['Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi', 'GPT4o']
    for auditor in auditors:
        audit_result_dir = os.path.join(audit_dir, auditor)
        if os.path.exists(audit_result_dir):
            for file in os.listdir(audit_result_dir):
                audit_result_csv_path = os.path.join(audit_dir, auditor, file)
                eval_csv_dir = os.path.join(evaluate_dir, auditor)
                os.makedirs(eval_csv_dir, exist_ok=True)
                eval_csv_path = os.path.join(eval_csv_dir, file)
                evaluate_audit_result_single_csv(
                    model=model, 
                    dataset=dataset,
                    auditor_name=auditor,
                    audit_result_path=audit_result_csv_path, 
                    eval_path=eval_csv_path, 
                    eval_mode=evaluate_mode)
        else:
            raise ValueError('audit result not found: ', audit_result_dir)
    print('finished')