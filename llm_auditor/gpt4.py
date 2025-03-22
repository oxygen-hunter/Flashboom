import os 
from pathlib import Path
import shutil
if __name__=='__main__':
    import sys
    p = Path(__file__).parent.parent
    os.chdir(p)
    sys.path.append(str(p))

import httpx
from openai import AzureOpenAI, OpenAI
import time

import os
from utils import get_txt_content_as_str
from llm_auditor.rag import build_user_prompt_for_same

class GPT4o:
    def __init__(self, subtype="openai/gpt-4o", source = 'open-router', temperature=0, **kwargs):
        self.subtype = subtype
        self.temperature = temperature
        if source == 'azure': 
            self.client = AzureOpenAI(
                api_version="2023-03-15-preview",
                http_client=httpx.Client(proxy="http://127.0.0.1:7890"),
                azure_endpoint="https://myopenai1233946.openai.azure.com/",
                api_key="-",
            )
        elif source == 'deep-bricks':
            self.client = OpenAI(
                http_client=httpx.Client(proxy="http://127.0.0.1:7890"),
                base_url="https://api.deepbricks.ai/v1/",
                api_key="-"
            )
        elif source == 'open-router':
            self.client = OpenAI(
                http_client=httpx.Client(proxy="http://127.0.0.1:7890"),
                base_url="https://openrouter.ai/api/v1",
                api_key="-"
            )

    def inference(self, system_prompt, user_prompt):
        start_time = time.time()
        data = [
            {"role": "system", "content": f"{system_prompt}"},
            {"role": "user", "content": f"{user_prompt}"},
        ]

        try:
            response = self.client.chat.completions.create(
            model=self.subtype,
            temperature=self.temperature,
            messages=data,
        )
        except Exception as e:
            print(e)
            time.sleep(10)
            print('try again')
            try:
                response = self.client.chat.completions.create(
                model=self.subtype,
                temperature=self.temperature,
                messages=data,
                )
            except Exception as e:
                print('fail again')
                inference_time = time.time() - start_time
                return (
                    'error: gpt4 fail',
                    0,
                    0,
                    inference_time
                )

        inference_time = time.time() - start_time

        return (
            response.choices[0].message.content,
            response.usage.prompt_tokens,
            response.usage.completion_tokens,
            inference_time
        )
    
    def build_system_prompt_for_same(self, ext):
        system_prompt_path = f'data/system_prompt/auditor/{ext}.txt'
        return get_txt_content_as_str(system_prompt_path)

    def build_user_prompt_for_same(self, todo_code, dataset, todo_filename, ext)->str:
        return build_user_prompt_for_same(todo_code, dataset, todo_filename, ext)
        
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

    
    def audit(self, audit_mode, todo_code, dataset, todo_filename):
        if audit_mode == 'no_rag':
            return self.no_rag_audit(todo_code, dataset, todo_filename)
        elif audit_mode == 'rag':
            return self.rag_audit(todo_code, dataset, todo_filename)
        
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
        return self.inference(system_prompt, user_prompt)