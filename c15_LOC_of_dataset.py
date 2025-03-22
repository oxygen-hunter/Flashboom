import os
from utils import get_function_ranges_of_source_code

def count_lines_of_code(file_path):
    """统计给定文件的代码行数（忽略空行）"""
    with open(file_path, 'r') as f:
        lines = [line for line in f if line.strip()]  # 去掉空行
    return len(lines)

def get_src_files_in_directory(directory, dataset, is_sample_dataset):
    """获取指定目录及其子目录中的所有.xx文件"""
    src_files = []
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(('.cpp', '.py', '.sol')):
                if is_sample_dataset:
                    # 算出了attention的source才计入统计
                    ext = '.'+file.split('.')[-1]
                    file_no_ext = file.split(ext)[0]
                    if dataset == 'messiq_dataset' or dataset == 'leetcode_cpp' or dataset == 'leetcode_python':
                        attn_dir = f'results/attention_view_vmax1/Mixtral/{dataset}'
                        attn_csv = os.path.join(attn_dir, file_no_ext+'.csv')
                        if os.path.exists(attn_csv):
                            src_files.append(os.path.join(root, file))
                    else:
                        raise ValueError('unknown dataset', dataset)
                else:
                    src_files.append(os.path.join(root, file))
    return src_files

def calculate_loc_statistics(directory, dataset, is_sample_dataset):
    """计算指定目录下所有.xx文件的平均、最大和最小代码行数"""
    src_files = get_src_files_in_directory(directory, dataset, is_sample_dataset)
    
    if not src_files:
        print(f"No source files found: {dataset}")
        return

    loc_list = [count_lines_of_code(file) for file in src_files]

    avg_loc = sum(loc_list) / len(loc_list)
    max_loc = max(loc_list)
    min_loc = min(loc_list)

    print('dataset: ', directory)
    print(f"Average LOC: {avg_loc}")
    print(f"Max LOC: {max_loc}")
    print(f"Min LOC: {min_loc}")

def calculate_function_count_statistics(directory, dataset, is_sample_dataset):
    src_files = get_src_files_in_directory(directory, dataset, is_sample_dataset)
    
    if not src_files:
        print("No source files found.")
        return

    range_list = []
    for file in src_files:
        ext = '.'+file.split('.')[-1]
        ranges = get_function_ranges_of_source_code(file, ext)
        if len(ranges):
            range_list.append(len(ranges))
        
    avg_func_count = sum(range_list) / len(range_list)
    max_func_count = max(range_list)
    min_func_count = min(range_list)
    print('dataset: ', directory)
    print(f"Average function count: {avg_func_count}")
    print(f"Max function count: {max_func_count}")
    print(f"Min function count: {min_func_count}")

messiq = 'data/messiq_dataset'
leetcode_cpp = 'data/leetcode_cpp'
leetcode_python = 'data/leetcode_python'
smartbugs = 'data/smartbugs-collection/code'
bigvul = 'data/big-vul-100/code'
cvefixes = 'data/cvefixes-100/code'

calculate_loc_statistics(messiq, 'messiq_dataset', is_sample_dataset=True)
calculate_loc_statistics(leetcode_cpp, 'leetcode_cpp', is_sample_dataset=True)
calculate_loc_statistics(leetcode_python, 'leetcode_python', is_sample_dataset=True)
calculate_loc_statistics(smartbugs, 'smartbugs-collection', is_sample_dataset=False)
calculate_loc_statistics(bigvul, 'big-vul-100', is_sample_dataset=False)
calculate_loc_statistics(cvefixes, 'cvefixes-100', is_sample_dataset=False)

print('-------')
calculate_function_count_statistics(messiq, 'messiq_dataset', is_sample_dataset=True)
calculate_function_count_statistics(leetcode_cpp, 'leetcode_cpp', is_sample_dataset=True)
calculate_function_count_statistics(leetcode_python, 'leetcode_python', is_sample_dataset=True)
calculate_function_count_statistics(smartbugs, 'smartbugs-collection', is_sample_dataset=False)
calculate_function_count_statistics(bigvul, 'big-vul-100', is_sample_dataset=False)
calculate_function_count_statistics(cvefixes, 'cvefixes-100', is_sample_dataset=False)