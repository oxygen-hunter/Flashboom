'''
insert highlight functions and its referenced contents to todo codes
'''


import re
import shutil

from utils import get_txt_content_as_lines, indexs_of_lines_start_with
import os

def insert_f_to_todo_code(contents:list, todo_code:list, insert_place:int):
    if insert_place <= len(todo_code):
        before = todo_code[:insert_place]
        after = todo_code[insert_place:]
        todo_code = before +['\n']+ contents +['\n']+ after
        return todo_code
    else:
        raise ValueError("insert place exceeds the length of todo code")



# insert place: the last contract's first line start with function/constructor
def find_insert_place(todo_code):
    contracts = indexs_of_lines_start_with(todo_code, 'contract ')
    if len(contracts):
        last_contract_index = contracts[-1]
        functions = indexs_of_lines_start_with(todo_code[last_contract_index:], ('function', 'constructor'))
        if len(functions):
            first_function_index = last_contract_index + functions[0]
            return first_function_index
        
    raise ValueError('insert place not found, todo_code: \n', todo_code)

# whether there is only one contract (no lib, no parent contract)
def sol_contains_single_contract(lines):
    contract_pattern = re.compile(r'^\s*(contract|interface|library)\s+(\w+)')
    contract_count = 0
    for line in lines:
        contract_match = contract_pattern.match(line)
        if contract_match:
            contract_count += 1
    
    return contract_count == 1


def process_one(contents_path, source_format, todo_code_path, output_path):
    if todo_code_path.endswith('.csv'):
        return True
    if source_format == '.sol':
        return process_one_solidity(contents_path, todo_code_path, output_path)
    elif source_format == '.py':
        return process_one_python(contents_path, todo_code_path, output_path)
    elif source_format == '.cpp':
        return process_one_cpp(contents_path, todo_code_path, output_path)
    else:
        raise ValueError(f'unkown format: {source_format}')
        return False

def process_one_solidity(contents_path, todo_code_path, output_path):
    contents = get_txt_content_as_lines(contents_path)
    if sol_contains_single_contract(contents):
        contents = contents[1:-1]
        todo_code = get_txt_content_as_lines(todo_code_path)
        insert_place = find_insert_place(todo_code)
        todo_code = insert_f_to_todo_code(contents, todo_code, insert_place)
        with open(output_path, 'w', encoding='utf-8') as f:
            f.writelines(todo_code)
        print('save to: ', output_path)
        return True
    else:
        print('not single contract')
        todo_code = get_txt_content_as_lines(todo_code_path)
        insert_place = len(todo_code) #find_insert_place(todo_code)
        todo_code = insert_f_to_todo_code(contents, todo_code, insert_place)
        with open(output_path, 'w', encoding='utf-8') as f:
            f.writelines(todo_code)
        print('save to: ', output_path)
        return True

def process_one_cpp(contents_path, todo_code_path, output_path):
    contents = get_txt_content_as_lines(contents_path)
    todo_code = get_txt_content_as_lines(todo_code_path)
    insert_place = len(todo_code)
    todo_code = insert_f_to_todo_code(contents, todo_code, insert_place)
    with open(output_path, 'w', encoding='utf-8') as f:
        f.writelines(todo_code)
    print('save to: ', output_path)
    return True

def process_one_python(contents_path, todo_code_path, output_path):
    contents = get_txt_content_as_lines(contents_path)
    # 缩进tab
    def dedent(lines):
        dedented_lines = []
        for line in lines:
            # 移除一个 tab 或 4 个空格的缩进
            if line.startswith('\t'):
                dedented_lines.append(line[1:])  # 移除一个 tab
            elif line.startswith('    '):
                dedented_lines.append(line[4:])  # 移除 4 个空格
            else:
                dedented_lines.append(line)  # 如果没有缩进，保持不变
        return dedented_lines
    contents = dedent(contents)
    todo_code = get_txt_content_as_lines(todo_code_path)
    if todo_code[0].startswith(('\t', '    ')):
        todo_code = dedent(todo_code)

    insert_place = len(todo_code)
    todo_code = insert_f_to_todo_code(contents, todo_code, insert_place)
    with open(output_path, 'w', encoding='utf-8') as f:
        f.writelines(todo_code)
    print('save to: ', output_path)
    return True

def test():
    contents_dir = 'function_slicer/llm_extractor_results/demo/GPT4'
    todo_code_dir = 'data/vuln-10/code'
    output_dir = 'data/vuln-10/add_attention_code/test'
    
    contents_file = '000-Heap.burn.sol'
    contents_file = '001-Hight.cc.sol'
    contents_file = '999-HeapX.burn.sol'
    contents_path = os.path.join(contents_dir, contents_file)
    for file in os.listdir(todo_code_dir):
        if file.endswith('.sol'):
            todo_code_path = os.path.join(todo_code_dir, file)
            output_path = os.path.join(output_dir, contents_file.split('.sol')[0])
            os.makedirs(output_path, exist_ok=True) # ../test/999-HeapX.burn
            output_path = os.path.join(output_path, file) # ../test/999-HeapX.burn/1_re_entrancy.sol
            succ = process_one(contents_path, todo_code_path, output_path)
            if not succ:
                shutil.rmtree(os.path.join(output_dir, contents_file.split('.sol')[0]))
                break


def batch_insert(contents_dir, todo_code_dir, output_dir):
    #contents_dir = 'function_slicer/llm_extractor_results/GPT4/Mixtral-top0-100'
    #contents_dir = 'function_slicer/llm_extractor_results/GPT4/Mixtral-random100'
    #todo_code_dir = 'data/vuln-10/code'
    #todo_code_dir = 'data/smartbugs-collection/code'
    #output_dir = 'data/vuln-10/add_attention_code/Mixtral/auto-random100'
    #output_dir = 'data/smartbugs-collection/add_attention_code/Mixtral/top0-100'
    
    for contents_file in os.listdir(contents_dir):
        # contents_file = '999-HeapX.burn.sol'
        if contents_file.endswith(('.sol', '.py', '.cpp')):
            source_format = '.'+contents_file.split('.')[-1]
            contents_path = os.path.join(contents_dir, contents_file)
            for file in os.listdir(todo_code_dir):
                todo_code_path = os.path.join(todo_code_dir, file)
                output_path = os.path.join(output_dir, contents_file.split(source_format)[0])
                os.makedirs(output_path, exist_ok=True) # ../auto/999-HeapX.burn
                output_path = os.path.join(output_path, file) # ../auto/999-HeapX.burn/1_re_entrancy.sol
                succ = process_one(contents_path, source_format, todo_code_path, output_path)
                if not succ:
                    shutil.rmtree(os.path.join(output_dir, contents_file.split(source_format)[0]))
                    break
