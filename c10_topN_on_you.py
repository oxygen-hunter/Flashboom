import os
import pandas as pd

'''
summary by llm
blind_name,yes_yes,yes_no,no_yes,no_no,blind_rate
'''
def my_topN_on_you(N, me, yous, summary_by_llm_dir):
    result = {}
    for you in yous:
        me_summary_by_llm_path = os.path.join(summary_by_llm_dir, me+'.csv')
        you_summary_by_llm_path = os.path.join(summary_by_llm_dir, you+'.csv')
        me_df = pd.read_csv(me_summary_by_llm_path)
        you_df = pd.read_csv(you_summary_by_llm_path)
        me_topN_methods = me_df['blind_name'].head(N).tolist()

        for method in me_topN_methods:
            if not method in result:
                result[method] = {}
            matches = you_df[you_df['blind_name'] == method]
            for index, row in matches.iterrows():
                n = index+1
                v = row['blind_rate']
                v_str = format(v, '.2f')
            result[method][you] = f"{v_str} ({n})"
    #print(result)
    latex_dict = pd.DataFrame.from_dict(result)
    latex_dict.columns = latex_dict.columns.str.replace('_', '\\_')
    latex_dict.columns = [x.split('.')[1] for x in latex_dict.columns]
    latex_dict = latex_dict.T

    print(latex_dict.to_latex(float_format='%.4f', column_format='p{2cm}r'))

def batch_me_topN_on_you(N, me, working_dir, evaluate_modes, judge_modes):
    if 'all' in evaluate_modes:
        evaluate_modes = ['yes_or_no', 'type', 'reason']
    if 'all' in judge_modes:
        judge_modes = ['yes_or_no', 'type']

    auditors = ['Mixtral', 'MixtralExpert', 'Gemma', 'Phi', 'CodeLlama', 'GPT4o']
    
    yous = auditors[:]
    
    for evaluate_mode in evaluate_modes:
        for judge_mode in judge_modes:
            summary_by_llm_dir = os.path.join(working_dir, 'summary_by_llm', evaluate_mode, judge_mode)
            my_topN_on_you(N=N, me=me, yous=yous, summary_by_llm_dir=summary_by_llm_dir)