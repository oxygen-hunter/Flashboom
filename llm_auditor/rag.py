import os 
from pathlib import Path
import shutil
if __name__=='__main__':
    import sys
    p = Path(__file__).parent.parent
    os.chdir(p)
    sys.path.append(str(p))

from utils import get_txt_content_as_str
import pandas as pd

def build_user_prompt_for_same(todo_code, dataset, todo_filename, ext)->str:
    def search_rag_code(todo_code, dataset, todo_filename):
        rag_code_dir = f'data/{dataset}/code'
        rag_expl_dir = f'data/{dataset}/explanation'
        rag_code_path = os.path.join(rag_code_dir, todo_filename)
        rag_expl_path = os.path.join(rag_expl_dir, todo_filename.replace(ext, '.txt'))
        vuln_detail_csv_path = f'data/{dataset}/code/vuln_detail.csv'
        # print(rag_code_path, rag_expl_path)
        if os.path.exists(rag_code_path):
            rag_code = get_txt_content_as_str(rag_code_path)
        else:
            raise ValueError('rag code file not found, todo filename: ', todo_filename)
        if os.path.exists(rag_expl_path):
            rag_expl = get_txt_content_as_str(rag_expl_path)
            vuln_type = ' '.join(todo_filename.split('_')[1:]).replace(ext, '')
            return rag_code, vuln_type, rag_expl
        elif os.path.exists(vuln_detail_csv_path):
            df = pd.read_csv(vuln_detail_csv_path)
            rag_expl = df.loc[df['file_name'] == todo_filename, 'explanation'].iloc[0]
            vuln_type = df.loc[df['file_name'] == todo_filename, 'vuln_type'].iloc[0]
            return rag_code, vuln_type, rag_expl
        else:
            raise ValueError('explanation or vuln_detail not found, todo filename: ', todo_filename)
        
        
    
    ext_map = {
        '.py': 'python',
        '.sol': 'smart contract',
        '.cpp': 'c++'
    }
    rag_prompt_template = """
    First review the following {lang} code. I am sure that it is vulnerable. The vulnerability type is {rag_vuln_type}.
    code:
    {rag_code}

    I will explan why it is vulnerable:
    {rag_explanation}

    Based on the given code, evaluate whether the following {lang} code is vulnerable.
    {todo_code}

    Your answer should in such format: first tell me 'YES' or 'NO', if 'YES', tell me why it is vulnerable, if 'NO', don't tell me anything more.
    """
    rag_code, rag_vuln_type, rag_explanation = search_rag_code(todo_code, dataset, todo_filename)
    return rag_prompt_template.format(
        rag_vuln_type=rag_vuln_type, 
        rag_code=rag_code, 
        rag_explanation=rag_explanation, 
        todo_code=todo_code,
        lang=ext_map[ext])