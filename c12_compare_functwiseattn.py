import json
import os
from c2_function_selection import functionwise_attention
from utils import linewise_attention_from_csv, get_txt_content_as_str, get_txt_content_as_lines, get_function_ranges_of_source_code, get_ext_by_dataset
import re
import pandas as pd
'''
results/attention_decrease/{vuln_dataset}/{analyzer}/{flashbang}.csv

     before after decrease decrease_rate
case1
case2
..
caseN
min
max
mean
'''

def vuln_func_attn_decrease_value(vuln_dataset, analyzer, flashbang, case_name):

    ext = get_ext_by_dataset(vuln_dataset)
    
    #flashbang = '7006-NameFilter.nameFilter' # read from json
    #case = '14_access_control' # all cases

    source_before_path = f'data/{vuln_dataset}/code/{case_name}{ext}'
    source_after_path = f'data/{vuln_dataset}/add_attention_code/{analyzer}/top0-100/{flashbang}/{case_name}{ext}'
    attn_before_path = f'results/attention_view_vmax1/{analyzer}/{vuln_dataset}/{case_name}.csv'
    attn_after_path = f'results/attention_view_vmax1/{analyzer}/{vuln_dataset}-flash/{flashbang}/{case_name}.csv'

    if not os.path.exists(attn_before_path):
        print(f'attn before not found: {flashbang}, {case_name}, {attn_before_path}, {attn_after_path}')
        #raise ValueError('')
        return 0,0,0,0
    if not os.path.exists(attn_after_path):
        print(f'attn after not found: {flashbang}, {case_name}, {attn_before_path}, {attn_after_path}')
        #raise ValueError('')
        return 0,0,0,0

    try:
        funcwise_attn_before = functionwise_attention(source_path=source_before_path, source_format=ext, csv_path=attn_before_path, sum_or_aver='sum')
        #print(funcwise_attn_before)
        funcwise_attn_after = functionwise_attention(source_path=source_after_path, source_format=ext, csv_path=attn_after_path, sum_or_aver='sum')
        #print('funcwise attn before:')
        #print(funcwise_attn_before)
        #print('funcwise attn after:')
        #print(funcwise_attn_after)
    except Exception as e:
        print(e)
        raise ValueError(f'parse error: {case_name}, {vuln_dataset}, {analyzer}, {flashbang}'
                         +f'\nsource_before_path:{source_before_path}, source_after_path:{source_after_path}')

    func_range_before = get_function_ranges_of_source_code(source_path=source_before_path, source_format=ext)
    if ext == '.sol':
        # find vuln func name in explanation
        explan_path = f'data/{vuln_dataset}/explanation/{case_name}.txt'
        # explan_str = get_txt_content_as_str(explan_path)
        # line_no_pattern = r'^The vulnerability lies in line (\d+):'
        # line_nos = re.findall(line_no_pattern, explan_str)
        # line_nos = [int(n) for n in line_nos]
        
        # vuln_func_names = set()
        # for line_no in line_nos:
        #     for func in func_range_before:
        #         func_start_line_no = func_range_before[func][0]
        #         func_end_line_no = func_range_before[func][1]
        #         if line_no <= func_end_line_no and line_no >= func_start_line_no:
        #             vuln_func_names.add(func)
        #             break
        # 提取explan中的所在行内容，去source中找它在哪一行
        vuln_func_names = set()
        code_lines_before = get_txt_content_as_lines(source_before_path)
        explan_lines = get_txt_content_as_lines(explan_path)
        for explan_line in explan_lines:
            if 'The vulnerability lies in line' in explan_line:
                content = explan_line.split(':')[-1].strip()
                content = content.split('//')[0]
                content = content.split('/*')[0]
                print(content)
                found = False
                for func in func_range_before:
                    func_start_line_no = func_range_before[func][0]
                    func_end_line_no = func_range_before[func][1]
                    func_lines = code_lines_before[func_start_line_no:func_end_line_no+1]
                    for func_line in func_lines:
                        if content in func_line:
                            vuln_func_names.add(func)
                            found = True
                            break
                    if found: break

    elif ext == '.cpp' or ext == '.py':
        # only one func
        
        vuln_func_names = set(func_range_before.keys())
        
    # 额外处理cpp，函数识别复杂，反向算flashbang的attn然后减掉
    if ext == '.cpp':
        vuln_func_name = 'empty'
        sum_of_attention = 0
        match analyzer:
            case 'Mixtral': sum_of_attention = 1024
            case 'CodeLlama': sum_of_attention = 1024
            case 'Phi': sum_of_attention = 1600
            case 'MixtralExpert': sum_of_attention = 1024
            case 'Gemma': sum_of_attention = 1024
        flashbang_attn_after = sum([funcwise_attn_after[k] for k in funcwise_attn_after])
        vuln_func_attn_before = sum_of_attention
        vuln_func_attn_after = sum_of_attention - flashbang_attn_after
    else:
        vuln_func_names = list(vuln_func_names)
        if len(vuln_func_names) == 0:
            raise ValueError(f'no vuln func found in case: {case_name}, {vuln_dataset}, {analyzer}, {flashbang}'
                            +f'\nsource_before_path:{source_before_path}, source_after_path:{source_after_path}')
                    
        # 有多个vuln_func的话取第一个
        vuln_func_name = vuln_func_names[0]
        vuln_func_attn_before = funcwise_attn_before[vuln_func_name]
        if not vuln_func_name in funcwise_attn_after:
            raise ValueError(f'vuln func not found after inserted blind module: {case_name}, {vuln_dataset}, {analyzer}, {flashbang}'
                            +f'\nsource_before_path:{source_before_path}, source_after_path:{source_after_path}'
                            +f'\nfunc_attn_before:{funcwise_attn_before} \nfunc_attn_after:{funcwise_attn_after}')
        vuln_func_attn_after = funcwise_attn_after[vuln_func_name]

    try:
        decrease = vuln_func_attn_before - vuln_func_attn_after
        decrease_rate = decrease / vuln_func_attn_before
    except Exception as e:
        print(e)
        # raise ValueError(f'calc error: {case_name}, {vuln_dataset}, {analyzer}, {flashbang}'
        #                  +f'\nsource_before_path:{source_before_path}, source_after_path:{source_after_path}'
        #                  +f'\nfunc_attn_before:{funcwise_attn_before} \nfunc_attn_after:{funcwise_attn_after}')
        decrease = 0
        decrease_rate = 0

    print(f'case_name: {case_name}, vuln func: {vuln_func_name}, attn before: {vuln_func_attn_before}, after: {vuln_func_attn_after}, decrease: {decrease}, decrease percent: {decrease_rate}')

    return vuln_func_attn_before, vuln_func_attn_after, decrease, decrease_rate


def batch_flashbang(vuln_dataset, analyzer, flashbang, csv_path):
    # if os.path.exists(csv_path):
    #     print(f'exist: {csv_path}')
    #     return
    df = pd.DataFrame(columns=['case_name', 'before', 'after', 'decrease', 'decrease_rate'])
    ext = get_ext_by_dataset(vuln_dataset)
    code_dir = f'data/{vuln_dataset}/code'
    files_order = sorted(os.listdir(code_dir), key=lambda x: int(x.split('_')[0]))
    for file in files_order:
        case_name = file.split(ext)[0]
        vuln_func_attn_before, vuln_func_attn_after, decrease, decrease_rate = vuln_func_attn_decrease_value(vuln_dataset, analyzer, flashbang, case_name)
        df.loc[len(df)] = {
            'case_name': case_name,
            'before': vuln_func_attn_before,
            'after': vuln_func_attn_after,
            'decrease': decrease,
            'decrease_rate': decrease_rate
        }
    df.to_csv(csv_path)

def batch(vuln_dataset, analyzer, json_path):
    with open(json_path) as f:
        d = json.load(f)

    ext = get_ext_by_dataset(vuln_dataset)
    flashbangs = [os.path.basename(k).split(ext)[0] for k in d.keys()]
    print('flashbangs:', flashbangs)
    
    csv_dir = f'results/attention_decrease/{vuln_dataset}/{analyzer}'
    os.makedirs(csv_dir, exist_ok=True)
    for flashbang in flashbangs:
        csv_path = f'results/attention_decrease/{vuln_dataset}/{analyzer}/{flashbang}.csv'
        batch_flashbang(vuln_dataset, analyzer, flashbang, csv_path)


datasets_pair = [
    #['messiq_dataset', 'smartbugs-collection' ],
    #['leetcode_cpp', 'big-vul-100'],
    #['leetcode_python', 'cvefixes-100']
]
analyzers = ['Mixtral', 'CodeLlama', 'Phi']
for vd in datasets_pair:
    sample_dataset = vd[0]
    vuln_dataset = vd[1]
    for analyzer in analyzers:
        json_path = f'function_selection/{sample_dataset}/{analyzer}/sum/100/summary.json'
        batch(vuln_dataset=vuln_dataset, analyzer=analyzer, json_path=json_path)
    print(f'{vd} finish')



datasets_pair = [
    ['messiq_dataset', 'smartbugs-collection' ],
]
analyzers = ['Gemma', 'MixtralExpert']
for vd in datasets_pair:
    sample_dataset = vd[0]
    vuln_dataset = vd[1]
    for analyzer in analyzers:
        json_path = f'function_selection/{sample_dataset}/{analyzer}/sum/100/summary.json'
        # if analyzer == 'MixtralExpert':
        #     json_path = f'function_selection/{sample_dataset}/{analyzer}/sum/100/last.json'
        batch(vuln_dataset=vuln_dataset, analyzer=analyzer, json_path=json_path)
    print(f'{vd} finish')