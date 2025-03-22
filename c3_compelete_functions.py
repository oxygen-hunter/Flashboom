import json
import shutil
from utils import get_txt_content_as_str
from utils_model import init_model
import torch
import os

def extract_referenced_contents(completer, slice_file, source_format, slice_file_content, source_path, output_path, runtime_path):
    if source_format == '.sol':
        return extract_referenced_contents_solidity(completer, slice_file, slice_file_content, source_path, output_path, runtime_path)
    elif source_format == '.cpp':
        return extract_referenced_contents_cpp(completer, slice_file, slice_file_content, source_path, output_path, runtime_path)
    elif source_format == '.py':
        return extract_referenced_contents_python(completer, slice_file, slice_file_content, source_path, output_path, runtime_path)

def extract_referenced_contents_solidity(completer, slice_file, slice_file_content, source_path, output_path, runtime_path):
    system_prompt = \
'''
You are an intelligent code assistant designed for extracting some specific function from a complete Solidity code.
I will give you a piece of complete solidity code, which contains several contracts, interfaces and libraries.
Your task is to extract the content of a specific function, along with all of its referenced contents. Here is how you can accomplish the task:
------
##INSTRUCTIONS:
- Target the specific function, with contract name and function name.
- View function code line by line, and record all symbols it used.
- Find the definition of these referenced symbols in other parts of Solidity code, including variables, functions, modifiers, events and so on.
- Extract the specific function and its directly referenced contents.
- If any referenced state variable is initalized in constructor function, do not include the constructor.
- Discard the pragma statement
'''

    user_prompt_template = \
'''
Please extract the following function and its referenced contents from the following Solidity code. You should discard all the irrelevant contents and just give me the intercepted code.

Function: {function_name}
Solidity code:
{source_code}

Please generate the response in Solidity code format.
DO NOT PROVIDE ANY OTHER OUTPUT TEXT OR EXPLANATION. DO NOT WRAP CODE WITH ```solidity```. Only provide the intercepted code.
'''
    #slice_file = '999-HeapX.burn.sol'
    function_name = slice_file.split('-')[-1].split('.sol')[0]
    source_code = get_txt_content_as_str(source_path)
    user_prompt = user_prompt_template.format(
        function_name = function_name,
        source_code = source_code
    )

    (results, input_token_length, output_token_length, inference_time) = completer.inference(system_prompt, user_prompt)

    # if gpt4 fails
    if results == 'error: gpt4 fail':
        results = \
"contract TempContract {\n"+\
slice_file_content+\
"\n}"

    # record runtime
    runtime = {}
    if os.path.exists(runtime_path):
        with open(runtime_path, 'r', encoding='utf-8') as f:
            runtime = json.load(f)
    runtime[output_path] = {
        'input_token_length': input_token_length,
        'output_token_length': output_token_length,
        'inference_time': inference_time
    }
    with open(runtime_path, 'w', encoding='utf-8') as f:
        json.dump(runtime, f, indent=2)
    with open(output_path, 'w', encoding='utf-8') as f:
        f.write(results)
    print('save to: ', output_path)
    

def extract_referenced_contents_cpp(completer, slice_file, slice_file_content, source_path, output_path, runtime_path):
    system_prompt = \
'''
You are an intelligent code assistant designed for extracting some specific function from a complete c++ code.
I will give you a piece of complete c++ code, which contains several classes.
Your task is to extract the content of a specific function, along with all of its referenced contents. Here is how you can accomplish the task:
------
##INSTRUCTIONS:
- Target the specific function, with class name and function name.
- View function code line by line, and record all symbols it used.
- Find the definition of these referenced symbols in other parts of c++ code, including variables, functions and so on.
- Extract the specific function and its directly referenced contents.
- If any referenced state variable is initalized in constructor function, do not include the constructor.
'''

    user_prompt_template = \
'''
Please extract the following function and its referenced contents from the following c++ code. You should discard all the irrelevant contents and just give me the intercepted code.

Function: {function_name}
c++ code:
{source_code}

Please generate the response in c++ code format.
DO NOT PROVIDE ANY OTHER OUTPUT TEXT OR EXPLANATION. DO NOT WRAP CODE WITH ```c++``` or ```cpp```. Only provide the intercepted code.
'''
    #slice_file = 'xx-xx-xx-aa.bb.cpp'
    function_name = slice_file.split('-')[-1].split('.cpp')[0]
    source_code = get_txt_content_as_str(source_path)
    user_prompt = user_prompt_template.format(
        function_name = function_name,
        source_code = source_code
    )

    (results, input_token_length, output_token_length, inference_time) = completer.inference(system_prompt, user_prompt)

    # if gpt4 fails
    if results == 'error: gpt4 fail':
        results = \
"class TempClass {\n"+\
slice_file_content+\
"\n}"

    # record runtime
    runtime = {}
    if os.path.exists(runtime_path):
        with open(runtime_path, 'r', encoding='utf-8') as f:
            runtime = json.load(f)
    runtime[output_path] = {
        'input_token_length': input_token_length,
        'output_token_length': output_token_length,
        'inference_time': inference_time
    }
    with open(runtime_path, 'w', encoding='utf-8') as f:
        json.dump(runtime, f, indent=2)
    with open(output_path, 'w', encoding='utf-8') as f:
        f.write(results)
    print('save to: ', output_path)


def extract_referenced_contents_python(completer, slice_file, slice_file_content, sol_source_path, output_path, runtime_path):
    system_prompt = \
'''
You are an intelligent code assistant designed for extracting some specific function from a complete python code.
I will give you a piece of complete python code, which contains several classes.
Your task is to extract the content of a specific function, along with all of its referenced contents. Here is how you can accomplish the task:
------
##INSTRUCTIONS:
- Target the specific function, with class name and function name.
- View function code line by line, and record all symbols it used.
- Find the definition of these referenced symbols in other parts of python code, including variables, functions and so on.
- Extract the specific function and its directly referenced contents.
- If any referenced state variable is initalized in constructor function, do not include the constructor.
'''

    user_prompt_template = \
'''
Please extract the following function and its referenced contents from the following python code. You should discard all the irrelevant contents and just give me the intercepted code.

Function: {function_name}
python code:
{source_code}

Please generate the response in python code format.
DO NOT PROVIDE ANY OTHER OUTPUT TEXT OR EXPLANATION. DO NOT WRAP CODE WITH ```python``` or ```python3```. Only provide the intercepted code.
'''
    #slice_file = 'xx-xx-xx-aa.bb.py'
    function_name = slice_file.split('-')[-1].split('.py')[0]
    source_code = get_txt_content_as_str(sol_source_path)
    user_prompt = user_prompt_template.format(
        function_name = function_name,
        solidity_code = source_code
    )

    (results, input_token_length, output_token_length, inference_time) = completer.inference(system_prompt, user_prompt)

    # if gpt4 fails
    if results == 'error: gpt4 fail':
        results = \
"class TempClass {\n"+\
slice_file_content+\
"\n}"

    # record runtime
    runtime = {}
    if os.path.exists(runtime_path):
        with open(runtime_path, 'r', encoding='utf-8') as f:
            runtime = json.load(f)
    runtime[output_path] = {
        'input_token_length': input_token_length,
        'output_token_length': output_token_length,
        'inference_time': inference_time
    }
    with open(runtime_path, 'w', encoding='utf-8') as f:
        json.dump(runtime, f, indent=2)
    with open(output_path, 'w', encoding='utf-8') as f:
        f.write(results)
    print('save to: ', output_path)


def batch_complete(analyzer, dataset, require, N):
    if dataset == 'messiq_dataset' or dataset == 'leetcode_cpp' or dataset == 'leetcode_python' \
        or dataset == 'leetcode_cpp_test' or dataset == 'leetcode_python_test':
        if dataset.startswith('messiq_dataset'):
            source_format = '.sol'
        elif dataset.startswith('leetcode_cpp'):
            source_format = '.cpp'
        elif dataset.startswith('leetcode_python'):
            source_format = '.py'

        selection_N_dir = f'function_selection/{dataset}/{analyzer}/{require}/{N}'
        selection_record_N_path = f'function_selection/{dataset}/{analyzer}/{require}/{N}/summary.json'
        complete_N_dir = f'function_completion/{dataset}/{analyzer}/{require}/{N}'
        complete_N_runtime_path = f'function_completion/{dataset}/{analyzer}/{require}/{N}/runtime.json'
        source_dir = f'data/{dataset}'
        if dataset.endswith('_test'):
            source_dir = f'data/{dataset.split('_test')[0]}'

        completer_name = 'GPT4o'
        completer = init_model(completer_name, max_new_tokens=1000)
        os.makedirs(complete_N_dir, exist_ok=True)

        if os.path.exists(selection_record_N_path):

            #   "function_selection/messiq_dataset/Phi/sum/all/2872-TeamTokenLock.getAllowedAmountByTeam.sol": 911.2298772335052,
            for slice_file in os.listdir(selection_N_dir):
                if slice_file.endswith(source_format):
                    #slice_file = 'xx-xx-xx-xx-aa.bb.cpp/py'
                    source_file_no_format = '-'.join(slice_file.split('-')[:-1])
                    source_path = os.path.join(source_dir, f'{source_file_no_format}{source_format}')
                    output_path = os.path.join(complete_N_dir, slice_file)
                    # cache
                    if os.path.exists(output_path):
                        print('existed: ', output_path)
                    
                    else:
                        cache_hit = False
                        cache_analyzers = ['Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi', 'GPT4o']
                        for analyzer in cache_analyzers:
                            other_output_dir = f'function_completion/{dataset}/{analyzer}/{require}/{N}'
                            other_output_path = os.path.join(other_output_dir, slice_file)
                            if os.path.exists(other_output_path):
                                shutil.copy(other_output_path, output_path)
                                other_runtime_path = os.path.join(other_output_dir, 'runtime.json')
                                with open(other_runtime_path, 'r', encoding='utf-8') as f:
                                    other_runtime = json.load(f)
                                runtime = {}
                                if os.path.exists(complete_N_runtime_path):
                                    with open(complete_N_runtime_path, 'r', encoding='utf-8') as f:
                                        runtime = json.load(f)
                                runtime[output_path] = other_runtime[other_output_path]
                                with open(complete_N_runtime_path, 'w', encoding='utf-8') as f:
                                    json.dump(runtime, f, indent=2)
                                print('computed: ', output_path)
                                cache_hit = True
                                break
                        if cache_hit:
                            pass
                        else:
                            slice_file_content = get_txt_content_as_str(os.path.join(selection_N_dir, slice_file))
                            extract_referenced_contents(
                                completer=completer, 
                                slice_file=slice_file, 
                                source_format = source_format,
                                slice_file_content=slice_file_content,
                                source_path=source_path, 
                                output_path=output_path,
                                runtime_path=complete_N_runtime_path)
        else:
            raise ValueError('functions not selected yet', selection_record_N_path)
        
        

# def test():
#     solidity_dir = 'data/messiq_dataset/contract1'
#     models = ['GPT4']
#     for model_name in models:
#         slice_file = '999-HeapX.burn.sol'
#         solidity_code_id = slice_file.split('-')[0]
#         solidity_code_path = os.path.join(solidity_dir, f'{solidity_code_id}.sol')
#         output_dir = f'function_slicer/llm_extractor_results/demo/{model_name}'
#         os.makedirs(output_dir, exist_ok=True)
#         output_path = os.path.join(output_dir, slice_file)
#         extract_referenced_contents(model_name, slice_file, solidity_code_path, output_path)


# if __name__ == '__main__':
#     #test()
#     batch()