'''
for those bs@exist bs@type cases in vuln dataset
results/attention_decrease_vs_bsr/{vuln_dataset}-{analyzer}-{flashbang}.png/pdf

results/{vuln_dataset}/add_attention_code/{analyzer}/top0-100/evaluate/type/{analyzer}/{flashbang}.csv / same_rag.csv

results/attention_decrease/{vuln_dataset}/{analyzer}/{flashbang}.csv
    before after decrease decrease_rate
'''



'''
eval report (evaluate/{eval_mode}/{auditor}/{method}.csv)
case_id, vuln_type, audit_report, gt, eval_score, eval_input_token_num, eval_output_token_num, eval_inerence_time

summary by llm (summary_by_llm/{eval_mode}/{auditor}.csv)
blind_name, yes_yes, yes_no, no_yes, no_no, blind_rate
'''
import os
from pathlib import Path

from matplotlib import pyplot as plt
import pandas as pd
import numpy as np


def get_succ_or_fail_cases(eval_csv_dir, flashbang, judge_mode, need_succ):

    result_list = []

    # same_rag
    same_rag_csv_path = os.path.join(eval_csv_dir, 'same_rag.csv')
    if not os.path.exists(same_rag_csv_path):
        raise ValueError('same_rag not found in ', eval_csv_dir)
    same_rag_df = pd.read_csv(same_rag_csv_path)
    
    # other method
    flashbang_csv_path = os.path.join(eval_csv_dir, f'{flashbang}.csv')
 
    flashbang_df = pd.read_csv(flashbang_csv_path)

    for index, row in flashbang_df.iterrows():
        same_rag_cell = int(same_rag_df.at[index, 'eval_score'])
        other_cell = int(flashbang_df.at[index, 'eval_score'])
        case_id = same_rag_df.at[index, 'case_id']
        vuln_type = same_rag_df.at[index, 'vuln_type'].replace(' ', '_')
        case_name = f'{case_id}_{vuln_type}'
        
        if judge_mode == 'yes_or_no':
            first_yes = same_rag_cell == 3 or same_rag_cell == 4 or same_rag_cell == 2
            second_yes = other_cell == 3 or other_cell == 4 or other_cell == 2 # strictly
        elif judge_mode == 'type':
            first_yes = same_rag_cell == 3 or same_rag_cell == 4
            second_yes = other_cell == 3 or other_cell == 4
        if need_succ:
            if first_yes and not second_yes:
                result_list.append(case_name)
        else:
            if first_yes and second_yes:
                result_list.append(case_name)

    return result_list


def draw_pic(df, vuln_dataset, analyzer, flashbang, judge_mode, need_succ):
    # 提取需要的数据
    case_names = df['case_name']
    after_values = df['after']
    decrease_values = df['decrease']

    # 绘制分段柱状图
    figsize=(8,4)
    plt.figure(figsize=figsize)
    fig, ax = plt.subplots(figsize=figsize)

    # 定义柱的 x 位置
    x = range(len(case_names))

    # 绘制 after 的部分
    deep_blue = '#00008B'
    light_blue = '#ADD8E6'
    ax.bar(x, after_values, label=r'$FuncwiseAtt(F_{vuln})$ after flashboom', color=deep_blue)

    # 绘制 decrease 的部分（叠加在 after 之上）
    ax.bar(x, decrease_values, bottom=after_values, label=r'decrease of $FuncwiseAtt(F_{vuln})$', color=light_blue)

    # 设置 x 轴标签
    ax.set_xticks(np.arange(min(x), max(x)+4, step=5))
    #ax.set_xticklabels(case_names, rotation=45, ha='right')

    # 添加图例和标签
    succ_str = 'Successful' if need_succ else 'Unsuccessful'
    ax.set_xlabel(f'{succ_str} blinding cases of flashboom {flashbang.split('-')[0]}')
    ax.set_ylabel(r'Attention value')
    if analyzer == 'Mixtral':
        ax.set_title(f'Model: Mistral')
    else:
        ax.set_title(f'Model: {analyzer}')
    #ax.set_title('Attention decrease of F_vuln after flashboom applied in each successful blinding case')
    ax.legend()

    succ_str = 'succ' if need_succ else 'fail'
    output_dir = f'results/attention_decrease_bar_for_{succ_str}_cases/{judge_mode}/'
    output_path_prefix = os.path.join(output_dir, f'{vuln_dataset}-{analyzer}-{flashbang}')

    os.makedirs(output_dir, exist_ok=True)

    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f'{output_path_prefix}.pdf', format='pdf', bbox_inches='tight')
    plt.close()
    print(f'saved to: {output_path_prefix}.pdf')


def filter_and_draw(vuln_dataset, analyzer, flashbang):

    df_path = f'results/attention_decrease/{vuln_dataset}/{analyzer}/{flashbang}.csv'
    eval_csv_dir = f'results/{vuln_dataset}/add_attention_code/{analyzer}/top0-100/evaluate/type/{analyzer}/'

    need_succs = [True, False]
    judge_modes = [
        #'yes_or_no',
        'type'
    ]

    fail_case_metrics = {}

    for need_succ in need_succs:
        for judge_mode in judge_modes:
            succ_cases = get_succ_or_fail_cases(eval_csv_dir=eval_csv_dir, flashbang=flashbang, judge_mode=judge_mode, need_succ=need_succ)
            attn_decrease_df = pd.read_csv(df_path)

            df = attn_decrease_df[attn_decrease_df['case_name'].isin(succ_cases)]

            df_positive = df['decrease'][df['decrease']>0]
            df_rate_positive = df['decrease_rate'][df['decrease_rate']>0]
            min_dec = df_positive.min()
            max_dec = df_positive.max() 
            mean_dec = df_positive.mean()
            min_dec_rate = df_rate_positive.min()
            max_dec_rate = df_rate_positive.max()
            mean_dec_rate = df_rate_positive.mean()
            #print(f'dataset: {vuln_dataset}, analyzer: {analyzer}, flashbang: {flashbang}, judge_mode: {judge_mode}, succ: {need_succ}')
            #print(f'decrease value min: {min_dec}, max: {max_dec}, mean: {mean_dec}')
            #print(f'decrease rate min: {min_dec_rate}, max: {max_dec_rate}, mean: {mean_dec_rate}')

            draw_pic(df=df, vuln_dataset=vuln_dataset, analyzer=analyzer, flashbang=flashbang, judge_mode=judge_mode, need_succ=need_succ)

            new_info = {
                'dataset': vuln_dataset,
                'analyzer': analyzer,
                'flashbang': flashbang,
                'judge_mode': judge_mode,
                'succ': need_succ,
                'min_dec': min_dec,
                'max_dec': max_dec,
                'mean_dec': mean_dec,
                'min_dec_rate': min_dec_rate,
                'max_dec_rate': max_dec_rate,
                'mean_dec_rate': mean_dec_rate
            }
            global summary_list
            summary_list.append(new_info)


            

'''
judge_mode:  yes_or_no
smartbugs-collection x Mixtral top1: 7006-NameFilter.nameFilter
smartbugs-collection x MixtralExpert top1: 7006-NameFilter.nameFilter
smartbugs-collection x Gemma top1: 2414-TerocoinToken.transfer
smartbugs-collection x CodeLlama top1: 603-wehome.transfer
smartbugs-collection x Phi top1: 8526-InitialMTTokenIMT._transferFrom

judge_mode: type
smartbugs-collection x Mixtral top1: 7006-NameFilter.nameFilter
smartbugs-collection x MixtralExpert top1: 7006-NameFilter.nameFilter
smartbugs-collection x Gemma top1: 2414-TerocoinToken.transfer
smartbugs-collection x CodeLlama top1: 1644-CustomToken.CustomToken
smartbugs-collection x Phi top1: 8002-LiterallyMinecraft.getCatImage
smartbugs-collection x Phi top2: '8526-InitialMTTokenIMT._transferFrom'
'''

summary_list = []
summary_df = pd.DataFrame()

if __name__ == '__main__':
    
    
    filter_and_draw('smartbugs-collection', 'Mixtral', '7006-NameFilter.nameFilter')
    filter_and_draw('smartbugs-collection', 'Mixtral', '3129-test.record_human_readable_blockhash')
    filter_and_draw('smartbugs-collection', 'Mixtral', '3671-Foo.doit')

    filter_and_draw('smartbugs-collection', 'MixtralExpert', '2912-Airdropper.multisend')
    filter_and_draw('smartbugs-collection', 'MixtralExpert', '7006-NameFilter.nameFilter')
    filter_and_draw('smartbugs-collection', 'MixtralExpert', '8543-ConvertLib.convert')

    filter_and_draw('smartbugs-collection', 'Gemma', '2414-TerocoinToken.transfer')
    filter_and_draw('smartbugs-collection', 'Gemma', '1673-Zlots._finishSpin')
    filter_and_draw('smartbugs-collection', 'Gemma', '6366-GameConfig.getUpgradeCardsInfo')
    
    
    # filter_and_draw('smartbugs-collection', 'CodeLlama', '1644-CustomToken.CustomToken')
    filter_and_draw('smartbugs-collection', 'CodeLlama', '603-wehome.transfer')
    filter_and_draw('smartbugs-collection', 'CodeLlama', '1721-StringYokes.zint_bytes32ToString')
    filter_and_draw('smartbugs-collection', 'CodeLlama', '1726-StringYokes.zint_bytes32ToString')
    
    
    filter_and_draw('smartbugs-collection', 'Phi', '8526-InitialMTTokenIMT._transferFrom')
    filter_and_draw('smartbugs-collection', 'Phi', '5996-MNYTiers.loadData')
    filter_and_draw('smartbugs-collection', 'Phi', '8002-LiterallyMinecraft.getCatImage')
    
    # low performance flashbooms

    filter_and_draw('smartbugs-collection', 'Mixtral', '9700-Airdrop.drop')
    filter_and_draw('smartbugs-collection', 'Mixtral', '6323-ParaTransfer.superTransfer')
    filter_and_draw('smartbugs-collection', 'Mixtral', '7041-Airdrop.drop')


    filter_and_draw('smartbugs-collection', 'MixtralExpert', '9689-CustomToken.CustomToken')
    filter_and_draw('smartbugs-collection', 'MixtralExpert', '9800-CustomToken.CustomToken')
    filter_and_draw('smartbugs-collection', 'MixtralExpert', '5285-CustomToken.CustomToken')

    filter_and_draw('smartbugs-collection', 'Gemma', '8931-DreamTokensVesting.withdrawTokens')
    filter_and_draw('smartbugs-collection', 'Gemma', '8929-DreamTokensVesting.withdrawTokens')
    filter_and_draw('smartbugs-collection', 'Gemma', '782-StandardToken.transferFrom')

    filter_and_draw('smartbugs-collection', 'CodeLlama', '4707-FreeDiceCoin.FreeDiceCoin')
    filter_and_draw('smartbugs-collection', 'CodeLlama', '2609-airdropManager.send')
    filter_and_draw('smartbugs-collection', 'CodeLlama', '4520-CustomToken.CustomToken')

    #filter_and_draw('smartbugs-collection', 'Phi', '9877-Authority.canCall')
    filter_and_draw('smartbugs-collection', 'Phi', '9390-EthereumExtreme.EthereumExtreme')
    filter_and_draw('smartbugs-collection', 'Phi', '7664-YOTOKEN.approveAndCall')
    filter_and_draw('smartbugs-collection', 'Phi', '8535-AdvertisementContract.AdvertisementPayout')
    
    
    

    summary_df = pd.DataFrame(summary_list)
    output_path = Path('results/attention_decrease_bar_summary/summary.csv')
    output_path.parent.mkdir(parents=True, exist_ok=True)
    summary_df.to_csv(output_path, index=False, float_format='%.4f')
    print(f'summary saved to {output_path}')