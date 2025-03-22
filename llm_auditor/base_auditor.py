import os 
from pathlib import Path
import shutil
if __name__=='__main__':
    import sys
    p = Path(__file__).parent.parent
    os.chdir(p)
    sys.path.append(str(p))

import time
from transformers import pipeline

import os
import csv
from transformers import AutoTokenizer, AutoModelForCausalLM, BitsAndBytesConfig
import torch
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
import numpy as np
import json
from tqdm import tqdm
import os
import pickle
from datetime import datetime
from utils import *
from llm_auditor.rag import build_user_prompt_for_same
import pandas as pd

class BaseAuditor:
    def __init__(
        self,
        max_new_tokens=300,
        begin_token="[INST]",
        end_token="[/INST]",
        support_system_prompt=False,
        linebreak='<0x0A>',
        **kwargs,
    ):
        self.max_new_tokens = max_new_tokens
        self.begin_token = begin_token
        self.end_token = end_token
        self.support_system_prompt = support_system_prompt
        self.linebreak = linebreak

    def direct_inference(self, system_prompt, user_prompt, model, tokenizer):
        # TODO: split by "your answer is xx" will lead to <end_of_turn> questions for model Gemma
        #user_prompt += "\nYour answer is:{end_token}".format(end_token=self.end_token)
        user_prompt += "\nYour answer is:"

        input_ids = tokenizer(user_prompt, return_tensors="pt").to("cuda")
        model.generation_config.pad_token_id = tokenizer.pad_token_id
        outputs = model.generate(**input_ids, max_new_tokens=self.max_new_tokens)
        results = tokenizer.decode(outputs[0]).split( 
            f"Your answer is:"
        )[-1]

        input_token_length = input_ids["input_ids"].shape[1]
        output_token_length = outputs[0].shape[0] - input_ids["input_ids"].shape[1]

        return results, input_token_length, output_token_length
    
    def pipeline_inference(self, system_prompt, user_prompt, model, tokenizer):
        if self.support_system_prompt:
            messages = [
                {"role": "system", "content": f"{system_prompt}"},
                {"role": "user", "content": f"{user_prompt}"},
            ]
        else:
            messages = [
                {"role": "user", "content": f"{system_prompt + '\n' + user_prompt}"},
            ]
        pipe = pipeline(
            "text-generation",
            model=model,
            tokenizer=tokenizer,
        )

        generation_args = {
            "max_new_tokens": self.max_new_tokens,
            "return_full_text": False,
            # "temperature": 0.0,
            # "do_sample": False,
            "pad_token_id": pipe.tokenizer.eos_token_id
        }

        outputs = pipe(messages, **generation_args)
        results = outputs[0]['generated_text']

        input_ids = tokenizer(user_prompt, return_tensors="pt").to("cuda")
        input_token_length = input_ids["input_ids"].shape[1]
        output_ids = tokenizer(results, return_tensors="pt").to("cuda")
        output_token_length = output_ids["input_ids"].shape[1]
        return results, input_token_length, output_token_length

    def inference(self, system_prompt, user_prompt):
        start_time = time.time()
        model = self.model
        tokenizer = self.tokenizer
        # if self.support_system_prompt:
        #     inference_method = self.pipeline_inference
        # else:
        #     inference_method = self.direct_inference

        inference_method = self.pipeline_inference

        results, input_token_length, output_token_length = inference_method(
            system_prompt, user_prompt, model, tokenizer
        )

        inference_time = time.time() - start_time

        return (results, input_token_length, output_token_length, inference_time)

    
    def build_system_prompt_for_same(self, ext):
        system_prompt_path = f'data/system_prompt/auditor/{ext}.txt'
        return get_txt_content_as_str(system_prompt_path)

    def build_user_prompt_for_same(self, todo_code, dataset, todo_filename, ext)->str:
        return build_user_prompt_for_same(todo_code, dataset, todo_filename, ext)
    

    def build_user_prompt_for_no_rag(todo_code):
        prompt_template = '''

        '''

    def audit(self, audit_mode, todo_code, dataset, todo_filename):
        if audit_mode == 'no_rag':
            return self.no_rag_audit(todo_code, dataset, todo_filename)
        else:
            return self.rag_audit(todo_code, dataset, todo_filename)
        
    def rag_audit(self, todo_code, dataset, todo_filename):
        ext = '.'+todo_filename.split('.')[-1]
        system_prompt = self.build_system_prompt_for_same(ext)
        user_prompt = self.build_user_prompt_for_same(todo_code, dataset, todo_filename, ext)
        return self.inference(system_prompt, user_prompt)
    
    def no_rag_audit(self, todo_code, dataset, todo_filename):
        system_prompt = \
'''
You are an intelligent code auditor designed for dectecting the vulnerabilitis for Solidity smart contract code.
Your task is to analyze the code and check if it contains any vulnerability (or potential attack, security issue and security risk) that you know.
'''
        user_prompt = \
f'''
Please audit the following smart contract code:

code:
{todo_code}

Provide your audit report include two things:
1. YES or NO, which means the existence of vulnerability (or potential attack, security issue and security risk)
2. A detailed explain of your judgement.

For example 'YES', your response should look like this: 'YES, the given smart contract code is vulnerable to a reentrancy attack.
The vulnerability lies in the transfer function, which calls the caddress contract's transferFrom function multiple times in a loop. If the caddress contract has a reentrancy vulnerability, it can be exploited to call the transfer function again, causing a recursive loop that can drain the contract's funds.
To fix this vulnerability, the caddress contract's transferFrom function should be made non-reentrant by using the "nonReentrant"'

For example 'NO', your response should look like this: 'NO, this smart contract is not vulnerable.'
'''
        return self.inference(system_prompt, user_prompt)
    

    def audit_malware(self, audit_mode, todo_code, todo_filename):
        system_prompt = ''
        user_prompt = \
f'''
Please detect whether the following code contains malware. 

code:
{todo_code}

Provide your detection report include two things:
1. YES or NO, which means the existence of vulnerability (or potential attack, security issue and security risk)
2. A detailed explain of your judgement.
'''
        return self.inference(system_prompt, user_prompt, self.model, self.tokenizer)

    
    def get_attention_old(self, token_ids):
        tokens = self.tokenizer.convert_ids_to_tokens(token_ids)
        output = self.model(token_ids.unsqueeze(0).to("cuda"), output_attentions=True)
        def get_layerwise_attention_sums(output):
            # Stack attention tensors from the output
            attentions_tensor = torch.stack(output.attentions)
            # print("Shape of attentions_tensor:", attentions_tensor.shape)
            # Select the first element in the batch for processing
            batch_attentions = attentions_tensor[:, 0, :, :, :]
            # Sum over heads for each layer
            layerwise_attentions = torch.sum(batch_attentions, dim=1)
            # Initialize list to hold summed attention matrices for each layer
            layerwise_attention_sums = []
            for layer in range(layerwise_attentions.shape[0]):
                # Get the sum of all heads for the current layer
                attention_sum = torch.sum(batch_attentions[layer], dim=0)
                layerwise_attention_sums.append(attention_sum)
            return layerwise_attention_sums
        def get_token_attention(attention_list):
            result = []
            for i_index in range(len(tokens)):
                    result.append((i_index, tokens[i_index], attention_list[len(tokens)-1][i_index].item()))
            return result
        res = get_layerwise_attention_sums(output)
        layers_attentions = [get_token_attention(layer_attention) for layer_attention in res]
        return layers_attentions
    

    def get_attention(self, token_ids):
        tokens = self.tokenizer.convert_ids_to_tokens(token_ids)
        # 1. 加torch.no_grad()
        with torch.no_grad():
            output = self.model(token_ids.unsqueeze(0).to("cuda"), output_attentions=True)
        
        # 2. 逐层分析+移到CPU，减少OOM可能
        def get_layerwise_attention_sums(output):
            # List to hold the summed attention matrices for each layer
            layerwise_attention_sums = []
            
            # Iterate through each layer in the attention outputs
            for layer_attention in output.attentions:
                # Select the first element in the batch (assuming batch_size=1)
                layer_attention = layer_attention[0]  # Shape: [num_heads, seq_len, seq_len]
                
                # Sum over heads for the current layer
                attention_sum = torch.sum(layer_attention, dim=0)  # Shape: [seq_len, seq_len]
                
                # Move to CPU and detach from the computation graph
                layerwise_attention_sums.append(attention_sum.detach().cpu())
                
                # Clear GPU memory after each layer processing
                del layer_attention, attention_sum
                torch.cuda.empty_cache()

            # Once all layers are processed, delete the output to free remaining memory
            del output
            torch.cuda.empty_cache()    
            return layerwise_attention_sums
        
        def get_token_attention(attention_list):
            result = []
            for i_index in range(len(tokens)):
                    result.append((i_index, tokens[i_index], attention_list[len(tokens)-1][i_index].item()))
            return result
        res = get_layerwise_attention_sums(output)
        layers_attentions = [get_token_attention(layer_attention) for layer_attention in res]
        return layers_attentions
        
    def prompt_to_token_ids(self, prompt):
        encoding = self.tokenizer(prompt, return_tensors="pt", return_offsets_mapping=False)
        return encoding['input_ids'][0]
    
    def show_attention(self, input_attention, output_path_prefix):
        #print('input attetion 0:\n', input_attention[0])
        
        # mask = [x[1] == self.linebreak for x in input_attention[0]]
        # lines = mask.count(True) + 1
        # matrix = np.zeros((lines, len(input_attention)))
        
        # # 遍历每一层
        # for layer in range(len(input_attention)):
        #     current_line = 0
        #     current_sum = 0
            
        #     # 遍历mask来计算每个序列的和
        #     for i, is_linebreak in enumerate(mask):
        #         current_sum += input_attention[layer][i][2]
        #         if is_linebreak:
        #             matrix[current_line, layer] = current_sum
        #             current_sum = 0
        #             current_line += 1
            
        #     # 处理最后一个序列
        #     matrix[current_line, layer] = current_sum

        # gemma会合并连续的\n，上限是31个，超过部分会开下一个token
        mask = [x[1].count(self.linebreak) for x in input_attention[0]]
        lines = sum(mask) + 1
        matrix = np.zeros((lines, len(input_attention)))
        
        # 遍历每一层
        for layer in range(len(input_attention)):
            current_line = 0
            current_sum = 0
            
            # 遍历mask来计算每个序列的和
            for i, line_break_count in enumerate(mask):
                current_sum += input_attention[layer][i][2]
                if line_break_count == 1:
                    matrix[current_line, layer] = current_sum
                    current_sum = 0
                    current_line += 1
                elif line_break_count >= 2:
                    matrix[current_line, layer] = current_sum
                    current_sum = 0
                    for i in range(current_line+1, current_line+line_break_count-1):
                        matrix[i, layer] = 0
                    current_line += line_break_count
            
            # 处理最后一个序列
            matrix[current_line, layer] = current_sum

        np.savetxt(f"{output_path_prefix}.csv", matrix, delimiter=',')
        # 可视化部分
        plt.figure(figsize=(len(input_attention), lines))
        cmap = mcolors.LinearSegmentedColormap.from_list('custom_cmap', ['white', 'blue'], N=256)
        #norm = mcolors.TwoSlopeNorm(vmin=0, vcenter=0.5, vmax=1)
        #norm = mcolors.TwoSlopeNorm(vmin=0, vcenter=3, vmax=5)
        norm = mcolors.TwoSlopeNorm(vmin=0, vcenter=15, vmax=31)
        plt.imshow(matrix, cmap=cmap, aspect='auto', norm=norm)
        plt.colorbar(label='Values')
        plt.title('Attention Visualization')
        plt.xlabel('Layers')
        plt.ylabel('Lines')
        plt.yticks(range(0, lines+1, 1))
        plt.xticks(range(0, len(input_attention), 1))
        plt.savefig(f'{output_path_prefix}.png', format='png')
        plt.savefig(f'{output_path_prefix}.svg', format='svg')
        plt.close()
        
    def draw_attention(self, prompt, output_path):
        start_time = time.time()
        # 1. prompt ->/*Tokenization*/ tokens 
        token_ids = self.prompt_to_token_ids(prompt)
        
        # 2. tokens ->/*LLM prefilling**/ attention maps
        attentions = self.get_attention(token_ids)
        
        # 3. draw line by line
        self.show_attention(attentions, output_path)

        time_used = time.time() - start_time
        return time_used