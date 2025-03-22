'''
input:
1. n.sol
2. attention csv of n.sol
output:
1. top1 function by attention sum
'''
import json
import random
import shutil

import os
from utils import get_function_ranges_of_source_code, linewise_attention_from_csv, get_txt_content_as_lines, save_function_content

def functionwise_attention(source_path, source_format, csv_path, sum_or_aver = 'sum')->dict:
    functions_range = get_function_ranges_of_source_code(source_path, source_format)

    #print('---\nfunctions_range:')
    #print(functions_range)
    #print('---')

    linewise_attention = linewise_attention_from_csv(csv_path)
    functionwise_attention_sum = {}
    functionwise_attention_aver = {}
    for name in functions_range:
        se = functions_range[name]
        start_line = se[0]
        end_line = se[1]
        functionwise_attention_sum[name] = sum(linewise_attention[start_line: end_line+1])
        functionwise_attention_aver[name] = sum(linewise_attention[start_line: end_line+1])/(end_line-start_line+1)

    if sum_or_aver == 'sum':
        return functionwise_attention_sum
    else:
        return functionwise_attention_aver
    
'''
select function from sol_source_path
save to output_path/{sol_id}-{function_name}.sol
'''
def select_required_function(source_path, source_format, attention_csv_path, output_path_format, require='sum'):
    print('processing ', source_path, ', ', attention_csv_path)
    if not os.path.exists(source_path):
        print('file not found: ', source_path)
        return
    if not os.path.exists(attention_csv_path):
        print('file not found: ', attention_csv_path)
        return
    
    functionwise_attention_sum = functionwise_attention(source_path, source_format, attention_csv_path, 'sum')
    if require == 'sum':
        # select function with max attention line sum
        max_attention = 0
        function_with_max_attention = ''
        for name in functionwise_attention_sum:
            if functionwise_attention_sum[name] > max_attention:
                function_with_max_attention = name
                max_attention = functionwise_attention_sum[name]
        
        if len(function_with_max_attention):
            save_function_content([function_with_max_attention], source_path, source_format, output_path_format)
            return output_path_format.format(function_name=function_with_max_attention), max_attention
        
        else:
            return '', 0
    elif require == 'random':
        if len(functionwise_attention_sum) > 0:
            random_function_name, its_attention = random.choice(list(functionwise_attention_sum.items()))
            save_function_content([random_function_name], source_path, source_format, output_path_format)
            return output_path_format.format(function_name=random_function_name), its_attention
        else:
            return '', 0

'''
collect N funcitons meet require from dataset x analyzer
record N functions {function_name:attention} to attention_record_path
output: 

messiq_dataset
attention_csv: results/attention_view_max1/{analyzer}/{dataset}
sol_source: data/{dataset}
output: function_selection/{dataset}/{analyzer}/{require}/{N}/1-function_name.sol
record: function_selection/{dataset}/{analyzer}/{require}/{N}/summary.json
'''
def batch_function_selection(analyzer, dataset, require, N):
    if dataset == 'messiq_dataset' or dataset == 'leetcode_cpp' or dataset == 'leetcode_python' \
        or dataset == 'leetcode_cpp_test' or dataset == 'leetcode_python_test':
        if dataset.startswith('messiq_dataset'):
            source_format = '.sol'
        elif dataset.startswith('leetcode_cpp'):
            source_format = '.cpp'
        elif dataset.startswith('leetcode_python'):
            source_format = '.py'
        
        selection_all_dir = f'function_selection/{dataset}/{analyzer}/{require}/all'
        selection_N_dir = f'function_selection/{dataset}/{analyzer}/{require}/{N}'
        record_all_path = f'function_selection/{dataset}/{analyzer}/{require}/all/summary.json'
        record_N_path = f'function_selection/{dataset}/{analyzer}/{require}/{N}/summary.json'
        source_dir = f'data/{dataset}'
        attention_csv_dir = f'results/attention_view_vmax1/{analyzer}/{dataset}'

        if dataset.endswith('_test'):
            source_dir = f'data/{dataset.split('_test')[0]}'
            if os.path.exists(record_all_path):
                os.remove(record_all_path)
            

        os.makedirs(selection_all_dir, exist_ok=True)
        if os.path.exists(selection_N_dir):
            shutil.rmtree(selection_N_dir)
        os.makedirs(selection_N_dir)

        if os.path.exists(record_all_path):
            record_all = json.load(open(record_all_path, 'r', encoding='utf-8'))
        else:
            record_all = {}
            for attention_csv_file in os.listdir(attention_csv_dir):
                if attention_csv_file.endswith('.csv'):
                    source_file = attention_csv_file.split('.csv')[0]+source_format
                    source_file_path = os.path.join(source_dir, source_file)
                    attention_csv_path = os.path.join(attention_csv_dir, attention_csv_file)
                    source_name_no_format = source_file.split(source_format)[0]
                    output_path_format = os.path.join(selection_all_dir, source_name_no_format+'-{function_name}'+source_format)
                    # select required function
                    function_sol_path_in_all, attention = select_required_function(
                        source_path=source_file_path,
                        source_format=source_format,
                        attention_csv_path=attention_csv_path, 
                        output_path_format=output_path_format, 
                        require=require)
                    if len(function_sol_path_in_all):
                        record_all[function_sol_path_in_all] = attention

            record_all = dict(sorted(record_all.items(), key=lambda item:item[1]))
            # save record all
            with open(record_all_path, 'w', encoding='utf-8') as f:
                json.dump(record_all, f, indent=2)
                print('record all saved to: ', record_all_path)

        # collect N and copy
        if require == 'random':
            random_N_keys = random.sample(list(record_all), N)
            record_N = {k:record_all[k] for k in random_N_keys}
        else:
            record_N = dict(sorted(record_all.items(), key=lambda item:item[1], reverse=True)[:N])

        for function_sol_path_in_all in record_N:
            if os.path.isfile(function_sol_path_in_all):
                shutil.copy(function_sol_path_in_all, selection_N_dir)
          
        # save record N
        with open(record_N_path, 'w', encoding='utf-8') as f:
            json.dump(record_N, f, indent=2)
            print('record N saved to: ', record_N_path)
    else:
        raise ValueError(f'unknown dataset {dataset}')



# def test():
#     sol_source_path = 'function_slicer/test_functionwise_attention/0.sol'
#     attention_csv_path = 'function_slicer/test_functionwise_attention/0.sol.csv'
#     output_path_format = 'function_slicer/test_functionwise_attention/0-{function_name}.sol'
#     select_required_function(sol_source_path, attention_csv_path, output_path_format)

# def test_n(n):
#     n = str(n)
#     sol_source_path = 'data/messiq_dataset/contract1/{n}.sol'.format(n=n)
#     attention_csv_path = 'results/attention_view_vmax1/Mixtral/messiq_dataset/contract1/{n}.sol.csv'.format(n=n)
#     output_path_format = 'function_slicer/test_functionwise_attention/{n}'.format(n=n)+'-{function_name}.sol'
#     select_required_function(sol_source_path, attention_csv_path, output_path_format)


# def random100attention():
#     all_dir = 'function_slicer/random_selected_functions/Mixtral'
#     random100_dir = 'function_slicer/random_selected_functions/Mixtral-random100'
#     record = 'function_slicer/random_selected_functions/summary/Mixtral.json'
#     record2 = 'function_slicer/random_selected_functions/summary/Mixtral-random100.json'

#     lst = [os.path.join(all_dir, x) for x in os.listdir(random100_dir)]
#     with open(record) as f:
#         rcd = json.load(f)

#     rcd2 = {x:rcd[x] for x in lst}

#     with open(record2, 'w') as f:
#         json.dump(rcd2, f, indent=2)
    


# '''
# copy keys of topN values in attention record (../xx.sol) to collect_dir
# '''
# def collect_topN_functions(attention_record_path, topN_collect_dir, topNstart=0, topNend=100):
#     with open(attention_record_path, 'r', encoding='utf-8') as f:
#         attention_record = json.load(f)

#     topN_keys = [k for k, v in sorted(attention_record.items(), key=lambda item: item[1], reverse=True)[topNstart:topNend]]

#     os.makedirs(topN_collect_dir, exist_ok=True)
#     for file in topN_keys:
#         if os.path.isfile(file):
#             shutil.copy(file, topN_collect_dir)

#     print('top{topNstart}-{topNend} saved to {dir}'.format(topNstart=topNstart, topNend=topNend, dir=topN_collect_dir))


# def task_collect_topN_functions(analyzer):
#     attention_record_path = f'function_slicer/attention_sum_top1_functions/summary/{analyzer}.json'
#     topNs = [0, 100, 200, 500, 1000, 2000]
#     for i in range(0, len(topNs)-1):
#         functions_topN_collect_dir = 'function_slicer/attention_sum_top1_functions/{model}-top{topNstart}-{topNend}'.format(model=analyzer, topNstart=topNs[i], topNend=topNs[i+1])
        
#         collect_topN_functions(attention_record_path, functions_topN_collect_dir, topNs[i], topNs[i+1])


# if __name__ == '__main__':
#     #test()
#     #test_n(53)
#     for i in range(1, 11):   
#         batch(source_group_id=i, model_name='Mixtral', require='random')

#     task_collect_topN_functions()
#     #random100attention()