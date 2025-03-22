import argparse

def main(args):
    
    # Execute corresponding task
    if args.task == 'compute_attention':
        print(f"Analyzers: {args.analyzers}, dataset: {args.dataset}, flash_json_path: {args.flash_json_path}, flash_code_par_dir: {args.flash_code_par_dir}, todo_code_par_dir: {args.todo_code_par_dir}")
        # Add your logic here for compute_attention
        import c1_attention_analyze
        c1_attention_analyze.batch_attention_analyze(args.analyzers, args.dataset, args.flash_json_path, args.flash_code_par_dir, args.todo_code_par_dir)
    
    elif args.task == 'select_function':
        print(f"Selecting functions for model {args.analyzer}, dataset: {args.dataset}, require: {args.require}, N: {args.N}")
        # Add your logic here for select_function
        import c2_function_selection
        c2_function_selection.batch_function_selection(analyzer=args.analyzer, dataset=args.dataset, require=args.require, N=args.N)

    elif args.task == 'complete_function':
        print(f"Completing functions for model {args.analyzer}, dataset: {args.dataset}, require: {args.require}, N: {args.N}")
        # Add your logic here for select_function
        import c3_compelete_functions
        c3_compelete_functions.batch_complete(analyzer=args.analyzer, dataset=args.dataset, require=args.require, N=args.N)
    
    elif args.task == 'insert_function':
        print(f"Inserting functions from {args.contents_dir} into code in {args.todo_code_dir}, outputting to {args.output_dir}")
        # Add your logic here for insert_function
        import c4_insert_f_to_todo_code
        c4_insert_f_to_todo_code.batch_insert(args.contents_dir, args.todo_code_dir, args.output_dir)

    elif args.task == 'audit':
        print(f"Auditors: {args.auditors}, dataset: {args.dataset}, todo_code_par_dir: {args.todo_code_par_dir}, audit_output_dir: {args.audit_output_dir}, audit_mode: {args.audit_mode}")
        # Add your logic here for audit
        import c5_audit
        c5_audit.batch_audit(auditors=args.auditors, dataset=args.dataset, todo_code_par_dir=args.todo_code_par_dir, audit_output_dir=args.audit_output_dir, audit_mode=args.audit_mode)

    elif args.task == 'evaluate':
        print(f"Evaluator: {args.evaluator}, dataset: {args.dataset}, auditors: {args.auditors}, working_dir: {args.working_dir}, eval_mode: {args.evaluate_mode}")
        # Add your logic here for evaluate
        import c6_evaluate_audit_result 
        c6_evaluate_audit_result.batch_eval(evaluator=args.evaluator, dataset=args.dataset, auditors=args.auditors, working_dir=args.working_dir, evaluate_mode=args.evaluate_mode)
    
    elif args.task == 'count_blind':
        print(f"Count blind spots in {args.working_dir}, eval_modes: {args.evaluate_modes}, judge_modes: {args.judge_modes}")
        # Add your logic here for count_blind
        import c7_count_blind
        c7_count_blind.batch_count_blind(working_dir=args.working_dir, evaluate_modes=args.evaluate_modes, judge_modes=args.judge_modes)
    elif args.task == 'draw_line':
        print(f"Draw line in {args.working_dir}, rank_path: {args.rank_path}, eval_modes: {args.evaluate_modes}")
        import c8_attention_rank_2_blind_rate_relationship
        c8_attention_rank_2_blind_rate_relationship.batch_draw_relationship(working_dir=args.working_dir, rank_path=args.rank_path, evaluate_modes=args.evaluate_modes)
    elif args.task == 'count_time':
        
        import c9_count_time
        if 'auditor' in args.phase:
            print(f"Count time for auditors: phase: {args.phase}, auditors: {args.auditors}, working_dir: {args.working_dir}")
            c9_count_time.time_of_auditors(auditors=args.auditors, working_dir=args.working_dir)
        if 'evaluator' in args.phase:
            print(f"Count time for evaluators: phase: {args.phase}, auditors: {args.auditors}, working_dir: {args.working_dir}, evaluate_modes: {args.evaluate_modes}")
            c9_count_time.time_of_evaluators(auditors=args.auditors, working_dir=args.working_dir, evaluate_modes=args.evaluate_modes)
    elif args.task == 'me_topN_on_you':
        print(f"TopN on you: N:{args.N}, me:{args.me}, working_dir:{args.working_dir}, evaluate_mode:{args.evaluate_modes}, judge_modes: {args.judge_modes}")
        import c10_topN_on_you
        c10_topN_on_you.batch_me_topN_on_you(N=args.N, me=args.me, working_dir=args.working_dir, evaluate_modes=args.evaluate_modes, judge_modes=args.judge_modes)
    elif args.task == 'audit_malware':
        print(f"Auditors: {args.auditors}, dataset: {args.dataset}, todo_code_par_dir: {args.todo_code_par_dir}, audit_output_dir: {args.audit_output_dir}, audit_mode: {args.audit_mode}")
        # Add your logic here for audit
        import c18_malware
        c18_malware.batch_audit(auditors=args.auditors, dataset=args.dataset, todo_code_par_dir=args.todo_code_par_dir, audit_output_dir=args.audit_output_dir, audit_mode=args.audit_mode)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Task processor for multiple functions.")
    
    # Create subparsers for different tasks
    subparsers = parser.add_subparsers(dest="task", help="Choose a task to run.")
    
    # 1. Compute attention
    compute_attention_parser = subparsers.add_parser('compute_attention', help='Compute attention using a specific model.')
    compute_attention_parser.add_argument('--analyzers', type=str, nargs='+', choices=['Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi'], required=True, help='Models to compute attention')
    compute_attention_parser.add_argument('--dataset', type=str, choices=['messiq_dataset', 'leetcode_cpp', 'leetcode_python', 'smartbugs-collection', 'big-vul-100', 'cvefixes-100', 'smartbugs', 'cppbugs-20'], required=True, help='Which dataset to analyze')
    compute_attention_parser.add_argument('--flash_json_path', type=str, required=False, default=None, help='A json where keys are paths to blind module. e.g., function_selection/leetcode_cpp/CodeLlama/sum/100/summary.json')
    compute_attention_parser.add_argument('--flash_code_par_dir', type=str, required=False, default=None, help='e.g., data/smartbugs-collection/add_attention_code/Mixtral/top0-100/261-EBU.transfer')
    compute_attention_parser.add_argument('--todo_code_par_dir', type=str, required=False, default=None, help='e.g., data/smartbugs')

    # 2. Select function
    select_function_parser = subparsers.add_parser('select_function', help='Select functions based on attention.')
    select_function_parser.add_argument('--analyzer', type=str, choices=['Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi'], required=True, help='Select function based on which models attention')
    select_function_parser.add_argument('--dataset', type=str, choices=['messiq_dataset', 'leetcode_cpp', 'leetcode_python', 'leetcode_cpp_test', 'leetcode_python_test'], required=True, help='Dataset for code base')
    select_function_parser.add_argument('--require', type=str, choices=['sum', 'random'], required=True, help='Selection criteria: sum or random')
    select_function_parser.add_argument('--N', type=int, required=True, help='Number of functions you need')

    # 3. Complete function
    complete_function_parser = subparsers.add_parser('complete_function', help='Complete selected functions with a model.')
    complete_function_parser.add_argument('--analyzer', choices=['Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi'], type=str, required=True, help='Select function based on which models attention')
    complete_function_parser.add_argument('--dataset', type=str, choices=['messiq_dataset', 'leetcode_cpp', 'leetcode_python', 'leetcode_cpp_test', 'leetcode_python_test'], required=True, help='Dataset for code base')
    complete_function_parser.add_argument('--require', type=str, choices=['sum', 'random'], required=True, help='Selection criteria: sum or random')
    complete_function_parser.add_argument('--N', type=int, required=True, help='Number of functions you need')

    # 4. Insert function
    insert_function_parser = subparsers.add_parser('insert_function', help='Insert functions into todo code.')
    insert_function_parser.add_argument('--contents_dir', type=str, required=True, help='Directory of completed functions. e.g., function_slicer/llm_extractor_results/GPT4/Mixtral-top0-100')
    insert_function_parser.add_argument('--todo_code_dir', type=str, required=True, help='Directory of code to modify. e.g., data/smartbugs-collection/code')
    insert_function_parser.add_argument('--output_dir', type=str, required=True, help='Directory for modified code output. e.g., data/smartbugs-collection/add_attention_code/Mixtral/top0-100')

    # 5. Audit
    audit_parser = subparsers.add_parser('audit', help='Audit code with specified models.')
    audit_parser.add_argument('--auditors', type=str, nargs='+', choices=['all', 'Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi', 'GPT4o'], default=["all"], help='Models to evaluate, e.g., all; specify multiple models by space (default: all)')
    audit_parser.add_argument('--dataset', type=str, choices=['vuln-10', 'smartbugs-collection', 'big-vul-100', 'cvefixes-100', 'smartbugs', 'cppbugs-20'], required=True, help='Dataset to audit')
    audit_parser.add_argument('--todo_code_par_dir', type=str, required=True, help='Directory of code to audit. e.g., data/smartbugs-collection/add_attention_code/Mixtral/top0-100')
    audit_parser.add_argument('--audit_output_dir', type=str, required=True, help='Directory for audit results. e.g., results/smartbugs-collection/add_attention_code/Mixtral/top0-100')
    audit_parser.add_argument('--audit_mode', type=str, choices=['rag', 'no_rag'], required=True, help='Audit mode')

    # 6. Evaluate
    evaluate_parser = subparsers.add_parser('evaluate', help='Evaluate audit results')
    evaluate_parser.add_argument('--evaluator', type=str, choices=['GPT4o'], default="GPT4o", help='Model for evaluation, default: GPT4o')
    evaluate_parser.add_argument('--dataset', type=str, choices=['vuln-10', 'smartbugs-collection', 'big-vul-100', 'cvefixes-100', 'smartbugs', 'cppbugs-20'], required=True, help='Dataset to audit')
    evaluate_parser.add_argument('--auditors', type=str, nargs='+', choices=['all', 'Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi', 'GPT4o'], default=["all"], help='Models to evaluate, e.g., all; specify multiple models by space (default: all)')
    evaluate_parser.add_argument('--working_dir', type=str, required=True, help='Directory of the work to evaluate, which contains a sub directory audit_result')
    evaluate_parser.add_argument('--evaluate_mode', type=str, choices=["yes_or_no", "type", "reason"], default="type", help="Mode of evaluation")

    # 7. Count blind 
    count_blind_parser = subparsers.add_parser('count_blind', help='Count blind.')
    count_blind_parser.add_argument('--working_dir', type=str, required=True, help='Working dir')
    count_blind_parser.add_argument('--evaluate_modes', type=str, nargs='+', choices=["all", "yes_or_no", "type", "reason"], default=['all'], help="Modes of evaluation")
    count_blind_parser.add_argument('--judge_modes', type=str, nargs='+', choices=["all", "yes_or_no", "type", "strict"], default=['all'], help="Modes of judgement, how to judge a successful audit")

    # 8. Draw line
    draw_line_parser = subparsers.add_parser('draw_line', help='Draw line.')
    draw_line_parser.add_argument('--working_dir', type=str, required=True, help='Working dir')
    draw_line_parser.add_argument('--rank_path', type=str, required=True, help='Json path of attention ranks of each method. e.g., function_slicer/attention_sum_top1_functions/summary/Mixtral.json')
    draw_line_parser.add_argument('--evaluate_modes', type=str, nargs='+', choices=["all", "yes_or_no", "type", "reason"], default=['all'], help="Modes of evaluation")

    # 9. Count time
    count_time_parser = subparsers.add_parser('count_time', help='Count time.')
    count_time_parser.add_argument('--phase', type=str, nargs='+', choices=['attention_analyzer', 'completer', 'auditor', 'evaluator'], required=True, help='count time for which phase')
    count_time_parser.add_argument('--auditors', type=str, nargs='+', choices=['all', 'Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi', 'GPT4o'], default=["all"], required=True, help = 'auditors in phase auditor/evaluator')
    count_time_parser.add_argument('--working_dir', type=str, required=True, help='Working dir')
    count_time_parser.add_argument('--evaluate_modes', type=str, nargs='+', choices=["all", "yes_or_no", "type", "reason"], default=['all'], help="Modes of evaluation")

    # 10. TopN on you
    topN_parser = subparsers.add_parser('me_topN_on_you', help='Me topN on you.')
    topN_parser.add_argument('--N', type=int, required=True, help='N')
    topN_parser.add_argument('--me', type=str, choices=['Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi', 'GPT4o'], required=True, help='me auditor')
    topN_parser.add_argument('--working_dir', type=str, required=True, help='Working dir')
    topN_parser.add_argument('--evaluate_modes', type=str, nargs='+', choices=["all", "yes_or_no", "type", "reason"], default=['all'], help="Modes of evaluation")
    topN_parser.add_argument('--judge_modes', type=str, nargs='+', choices=["all", "yes_or_no", "type"], default=['all'], help="Modes of judgement, how to judge a successful audit")

    malware_parser = subparsers.add_parser('audit_malware', help='Audit malware code.')
    malware_parser.add_argument('--auditors', type=str, nargs='+', choices=['all', 'Mixtral', 'MixtralExpert', 'Gemma', 'CodeLlama', 'Phi', 'GPT4o'], default=["all"], help='Models to evaluate, e.g., all; specify multiple models by space (default: all)')
    malware_parser.add_argument('--dataset', type=str, choices=['malware-10'], required=True, help='Dataset to audit')
    malware_parser.add_argument('--todo_code_par_dir', type=str, required=True, help='Directory of code to audit. e.g., data/smartbugs-collection/add_attention_code/Mixtral/top0-100')
    malware_parser.add_argument('--audit_output_dir', type=str, required=True, help='Directory for audit results. e.g., results/smartbugs-collection/add_attention_code/Mixtral/top0-100')
    malware_parser.add_argument('--audit_mode', type=str, choices=['rag', 'no_rag'], required=True, help='Audit mode')

    
    args = parser.parse_args()

    main(args)

