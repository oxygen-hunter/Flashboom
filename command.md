## 1 attention analyze
python main.py compute_attention --analyzers Gemma CodeLlama MixtralExpert --dataset messiq_dataset

nohup python main.py compute_attention --analyzers Mixtral --dataset leetcode_cpp > log/Mixtral.analyze.leetcode_cpp.log 2>&1 &

nohup python main.py compute_attention --analyzers Mixtral --dataset leetcode_python > log/Mixtral.analyze.leetcode_python.log 2>&1 &

nohup python main.py compute_attention --analyzers Phi --dataset leetcode_cpp > log/Phi.analyze.leetcode_cpp.log 2>&1 &

nohup python main.py compute_attention --analyzers Phi --dataset leetcode_python > log/Phi.analyze.leetcode_python.log 2>&1 &

nohup python main.py compute_attention --analyzers CodeLlama --dataset leetcode_cpp > log/CodeLlama.analyze.leetcode_cpp.log 2>&1 &

nohup python main.py compute_attention --analyzers CodeLlama --dataset leetcode_python > log/CodeLlama.analyze.leetcode_python.log 2>&1 &

nohup python main.py compute_attention --analyzers Gemma --dataset leetcode_cpp > log/Gemma.analyze.leetcode_cpp.log 2>&1 &

nohup python main.py compute_attention --analyzers Gemma --dataset leetcode_python > log/Gemma.analyze.leetcode_python.log 2>&1 &

nohup python main.py compute_attention --analyzers MixtralExpert --dataset leetcode_cpp > log/MixtralExpert.analyze.leetcode_cpp.log 2>&1 &

nohup python main.py compute_attention --analyzers MixtralExpert --dataset leetcode_python > log/MixtralExpert.analyze.leetcode_python.log 2>&1 &

### verification
#### sol
nohup python main.py compute_attention --analyzers Mixtral --dataset smartbugs-collection --flash_json_path function_selection/messiq_dataset/Mixtral/sum/100/summary.json --flash_code_par_dir data/smartbugs-collection/add_attention_code/Mixtral/top0-100 > log/sol.Mixtral.top0-100.veriAttn.log 2>&1 &

nohup python main.py compute_attention --analyzers Phi --dataset smartbugs-collection --flash_json_path function_selection/messiq_dataset/Phi/sum/100/summary.json --flash_code_par_dir data/smartbugs-collection/add_attention_code/Phi/top0-100 > log/sol.Phi.top0-100.veriAttn.log 2>&1 &

nohup python main.py compute_attention --analyzers CodeLlama --dataset smartbugs-collection --flash_json_path function_selection/messiq_dataset/CodeLlama/sum/100/summary.json --flash_code_par_dir data/smartbugs-collection/add_attention_code/CodeLlama/top0-100 > log/sol.CodeLlama.top0-100.veriAttn.log 2>&1 &

nohup python main.py compute_attention --analyzers Gemma --dataset smartbugs-collection --flash_json_path function_selection/messiq_dataset/Gemma/sum/100/summary.json --flash_code_par_dir data/smartbugs-collection/add_attention_code/Gemma/top0-100 > log/sol.Gemma.top0-100.veriAttn.log 2>&1 &

nohup python main.py compute_attention --analyzers MixtralExpert --dataset smartbugs-collection --flash_json_path function_selection/messiq_dataset/MixtralExpert/sum/100/summary.json --flash_code_par_dir data/smartbugs-collection/add_attention_code/MixtralExpert/top0-100 > log/sol.MixtralExpert.top0-100.veriAttn.log 2>&1 &

#### only the last
nohup python main.py compute_attention --analyzers MixtralExpert --dataset smartbugs-collection --flash_json_path function_selection/messiq_dataset/MixtralExpert/sum/100/last.json --flash_code_par_dir data/smartbugs-collection/add_attention_code/MixtralExpert/top0-100 > log/sol.MixtralExpert.top0-100.veriAttn.log 2>&1 &

#### for baselines
nohup python main.py compute_attention --analyzers Mixtral --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/baselines > log/sol.Mixtral.baselines.veriAttn.log 2>&1 &

#### specify
type
Phi top1: 8002-LiterallyMinecraft.getCatImage
Gemma top1: 2414-TerocoinToken.transfer
MixtralExpert top1: 7006-NameFilter.nameFilter

nohup python main.py compute_attention --analyzers Gemma --dataset smartbugs-collection --flash_json_path function_selection/messiq_dataset/Gemma/sum/1/summary.json --flash_code_par_dir data/smartbugs-collection/add_attention_code/Gemma/top0-100 > log/sol.Gemma.top0-100.veriAttn.log 2>&1 &

nohup python main.py compute_attention --analyzers MixtralExpert --dataset smartbugs-collection --flash_json_path function_selection/messiq_dataset/MixtralExpert/sum/1/summary.json --flash_code_par_dir data/smartbugs-collection/add_attention_code/MixtralExpert/top0-100 > log/sol.MixtralExpert.top0-100.veriAttn.log 2>&1 &

#### cpp
nohup python main.py compute_attention --analyzers Mixtral --dataset big-vul-100 --flash_json_path function_selection/leetcode_cpp/Mixtral/sum/100/summary.json --flash_code_par_dir data/big-vul-100/add_attention_code/Mixtral/top0-100 > log/cpp.Mixtral.top0-100.veriAttn.log 2>&1 &

nohup python main.py compute_attention --analyzers Phi --dataset big-vul-100 --flash_json_path function_selection/leetcode_cpp/Phi/sum/100/summary.json --flash_code_par_dir data/big-vul-100/add_attention_code/Phi/top0-100 > log/cpp.Phi.top0-100.veriAttn.log 2>&1 &

nohup python main.py compute_attention --analyzers CodeLlama --dataset big-vul-100 --flash_json_path function_selection/leetcode_cpp/CodeLlama/sum/100/summary.json --flash_code_par_dir data/big-vul-100/add_attention_code/CodeLlama/top0-100 > log/cpp.CodeLlama.top0-100.veriAttn.log 2>&1 &


#### py

nohup python main.py compute_attention --analyzers Mixtral --dataset cvefixes-100 --flash_json_path function_selection/leetcode_python/Mixtral/sum/100/summary.json --flash_code_par_dir data/cvefixes-100/add_attention_code/Mixtral/top0-100 > log/py.Mixtral.top0-100.veriAttn.log 2>&1 &

nohup python main.py compute_attention --analyzers Phi --dataset cvefixes-100 --flash_json_path function_selection/leetcode_python/Phi/sum/100/summary.json --flash_code_par_dir data/cvefixes-100/add_attention_code/Phi/top0-100 > log/py.Phi.top0-100.veriAttn.log 2>&1 &

nohup python main.py compute_attention --analyzers CodeLlama --dataset cvefixes-100 --flash_json_path function_selection/leetcode_python/CodeLlama/sum/100/summary.json --flash_code_par_dir data/cvefixes-100/add_attention_code/CodeLlama/top0-100 > log/py.CodeLlama.top0-100.veriAttn.log 2>&1 &
-



## 2 function selection
python main.py select_function --analyzer Phi --dataset messiq_dataset --require sum --N 100
python main.py select_function --analyzer Mixtral --dataset messiq_dataset --require sum --N 100
python main.py select_function --analyzer MixtralExpert --dataset messiq_dataset --require sum --N 100
python main.py select_function --analyzer Gemma --dataset messiq_dataset --require sum --N 100
python main.py select_function --analyzer CodeLlama --dataset messiq_dataset --require sum --N 100

python main.py select_function --analyzer Mixtral --dataset messiq_dataset --require random --N 3

### cpp
python main.py select_function --analyzer Mixtral --dataset leetcode_cpp_test --require sum --N 100
python main.py select_function --analyzer Mixtral --dataset leetcode_cpp --require sum --N 100
python main.py select_function --analyzer Phi --dataset leetcode_cpp --require sum --N 100
python main.py select_function --analyzer CodeLlama --dataset leetcode_cpp --require sum --N 100

python main.py select_function --analyzer MixtralExpert --dataset leetcode_cpp --require sum --N 100
python main.py select_function --analyzer Gemma --dataset leetcode_cpp --require sum --N 100

python main.py select_function --analyzer Mixtral --dataset leetcode_cpp --require random --N 3

### py
python main.py select_function --analyzer Mixtral --dataset leetcode_python_test --require sum --N 100
python main.py select_function --analyzer Mixtral --dataset leetcode_python --require sum --N 100
python main.py select_function --analyzer Phi --dataset leetcode_python --require sum --N 100
python main.py select_function --analyzer CodeLlama --dataset leetcode_python --require sum --N 100

python main.py select_function --analyzer MixtralExpert --dataset leetcode_python --require sum --N 100
python main.py select_function --analyzer Gemma --dataset leetcode_python --require sum --N 100

python main.py select_function --analyzer Mixtral --dataset leetcode_python --require random --N 3

## 3 function completion
python main.py complete_function --analyzer Phi --dataset messiq_dataset --require sum --N 100
python main.py complete_function --analyzer Gemma --dataset messiq_dataset --require sum --N 100
python main.py complete_function --analyzer CodeLlama --dataset messiq_dataset --require sum --N 100
python main.py complete_function --analyzer MixtralExpert --dataset messiq_dataset --require sum --N 100
python main.py complete_function --analyzer Mixtral --dataset messiq_dataset --require sum --N 100
python main.py complete_function --analyzer Mixtral --dataset messiq_dataset --require random --N 3

python main.py complete_function --analyzer Mixtral --dataset leetcode_cpp_test --require sum --N 100
python main.py complete_function --analyzer Mixtral --dataset leetcode_cpp --require sum --N 100



## 4 insert f
### sol (complete)
python main.py insert_function --contents_dir function_completion/messiq_dataset/Phi/sum/100 --todo_code_dir data/smartbugs-collection/code --output_dir data/smartbugs-collection/add_attention_code/Phi/top0-100
python main.py insert_function --contents_dir function_completion/messiq_dataset/Gemma/sum/100 --todo_code_dir data/smartbugs-collection/code --output_dir data/smartbugs-collection/add_attention_code/Gemma/top0-100
python main.py insert_function --contents_dir function_completion/messiq_dataset/CodeLlama/sum/100 --todo_code_dir data/smartbugs-collection/code --output_dir data/smartbugs-collection/add_attention_code/CodeLlama/top0-100
python main.py insert_function --contents_dir function_completion/messiq_dataset/MixtralExpert/sum/100 --todo_code_dir data/smartbugs-collection/code --output_dir data/smartbugs-collection/add_attention_code/MixtralExpert/top0-100
python main.py insert_function --contents_dir function_completion/messiq_dataset/Mixtral/sum/100 --todo_code_dir data/smartbugs-collection/code --output_dir data/smartbugs-collection/add_attention_code/MixtralExpert/top0-100

python main.py insert_function --contents_dir function_completion/messiq_dataset/Mixtral/random/3 --todo_code_dir data/smartbugs-collection/code --output_dir data/smartbugs-collection/baselines


### cpp (no complete)
python main.py insert_function --contents_dir function_selection/leetcode_cpp/Mixtral/sum/100 --todo_code_dir data/big-vul-100/code --output_dir data/big-vul-100/add_attention_code/Mixtral/top0-100

python main.py insert_function --contents_dir function_selection/leetcode_cpp/Phi/sum/100 --todo_code_dir data/big-vul-100/code --output_dir data/big-vul-100/add_attention_code/Phi/top0-100

python main.py insert_function --contents_dir function_selection/leetcode_cpp/CodeLlama/sum/100 --todo_code_dir data/big-vul-100/code --output_dir data/big-vul-100/add_attention_code/CodeLlama/top0-100

python main.py insert_function --contents_dir function_selection/leetcode_cpp/Gemma/sum/100 --todo_code_dir data/big-vul-100/code --output_dir data/big-vul-100/add_attention_code/Gemma/top0-100

python main.py insert_function --contents_dir function_selection/leetcode_cpp/MixtralExpert/sum/100 --todo_code_dir data/big-vul-100/code --output_dir data/big-vul-100/add_attention_code/MixtralExpert/top0-100

python main.py insert_function --contents_dir function_selection/leetcode_cpp/Mixtral/random/3 --todo_code_dir data/big-vul-100/code --output_dir data/big-vul-100/baselines

### py (no complete)
python main.py insert_function --contents_dir function_selection/leetcode_python/Mixtral/sum/100 --todo_code_dir data/cvefixes-100/code --output_dir data/cvefixes-100/add_attention_code/Mixtral/top0-100

python main.py insert_function --contents_dir function_selection/leetcode_python/Phi/sum/100 --todo_code_dir data/cvefixes-100/code --output_dir data/cvefixes-100/add_attention_code/Phi/top0-100

python main.py insert_function --contents_dir function_selection/leetcode_python/CodeLlama/sum/100 --todo_code_dir data/cvefixes-100/code --output_dir data/cvefixes-100/add_attention_code/CodeLlama/top0-100

python main.py insert_function --contents_dir function_selection/leetcode_python/Gemma/sum/100 --todo_code_dir data/cvefixes-100/code --output_dir data/cvefixes-100/add_attention_code/Gemma/top0-100

python main.py insert_function --contents_dir function_selection/leetcode_python/MixtralExpert/sum/100 --todo_code_dir data/cvefixes-100/code --output_dir data/cvefixes-100/add_attention_code/MixtralExpert/top0-100

python main.py insert_function --contents_dir function_selection/leetcode_python/Mixtral/random/3 --todo_code_dir data/cvefixes-100/code --output_dir data/cvefixes-100/baselines

## 5 audit
python main.py audit --auditors GPT4o --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/add_attention_code/Mixtral/top0-100 --audit_output_dir results/smartbugs-collection/add_attention_code/Mixtral/top0-100 --audit_mode rag

python main.py audit --auditors MixtralExpert CodeLlama --dataset smartbugs-collection --todo_code_par_dir none --audit_output_dir results/smartbugs-collection/add_attention_code/Mixtral/top0-100 --audit_mode no_rag

### audit for self
#### sol
python main.py audit --auditors Mixtral --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/add_attention_code/Mixtral/top0-100 --audit_output_dir results/smartbugs-collection/add_attention_code/Mixtral/top0-100 --audit_mode rag

python main.py audit --auditors Phi --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/add_attention_code/Phi/top0-100 --audit_output_dir results/smartbugs-collection/add_attention_code/Phi/top0-100 --audit_mode rag

nohup python main.py audit --auditors Gemma --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/add_attention_code/Gemma/top0-100 --audit_output_dir results/smartbugs-collection/add_attention_code/Gemma/top0-100 --audit_mode rag > log/Gemma.audit.log 2>&1 &

nohup python main.py audit --auditors CodeLlama --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/add_attention_code/CodeLlama/top0-100 --audit_output_dir results/smartbugs-collection/add_attention_code/CodeLlama/top0-100 --audit_mode rag > log/CodeLlama.audit.log 2>&1 &

nohup python main.py audit --auditors MixtralExpert --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/add_attention_code/MixtralExpert/top0-100 --audit_output_dir results/smartbugs-collection/add_attention_code/MixtralExpert/top0-100 --audit_mode rag > log/MixtralExpert.log 2>&1 &
##### sol mixtral cross
python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/add_attention_code/Mixtral/top0-100 --audit_output_dir results/smartbugs-collection/add_attention_code/Mixtral/top0-100 --audit_mode rag


#### c++
nohup python main.py audit --auditors Mixtral --dataset big-vul-100 --todo_code_par_dir data/big-vul-100/add_attention_code/Mixtral/top0-100 --audit_output_dir results/big-vul-100/add_attention_code/Mixtral/top0-100 --audit_mode rag > log/Mixtral.big-vul100.audit.log 2>&1  &

nohup python main.py audit --auditors Phi --dataset big-vul-100 --todo_code_par_dir data/big-vul-100/add_attention_code/Phi/top0-100 --audit_output_dir results/big-vul-100/add_attention_code/Phi/top0-100 --audit_mode rag > log/Phi.big-vul100.audit.log 2>&1  &

nohup python main.py audit --auditors CodeLlama --dataset big-vul-100 --todo_code_par_dir data/big-vul-100/add_attention_code/CodeLlama/top0-100 --audit_output_dir results/big-vul-100/add_attention_code/CodeLlama/top0-100 --audit_mode rag > log/CodeLlama.big-vul100.audit.log 2>&1  &

nohup python main.py audit --auditors Gemma --dataset big-vul-100 --todo_code_par_dir data/big-vul-100/add_attention_code/Gemma/top0-100 --audit_output_dir results/big-vul-100/add_attention_code/Gemma/top0-100 --audit_mode rag > log/Gemma.big-vul100.audit.log 2>&1  &

nohup python main.py audit --auditors MixtralExpert --dataset big-vul-100 --todo_code_par_dir data/big-vul-100/add_attention_code/MixtralExpert/top0-100 --audit_output_dir results/big-vul-100/add_attention_code/MixtralExpert/top0-100 --audit_mode rag > log/MixtralExpert.big-vul100.audit.log 2>&1  &

#### py
nohup python main.py audit --auditors Mixtral --dataset cvefixes-100 --todo_code_par_dir data/cvefixes-100/add_attention_code/Mixtral/top0-100 --audit_output_dir results/cvefixes-100/add_attention_code/Mixtral/top0-100 --audit_mode rag > log/Mixtral.cvefixes-100.audit.log 2>&1  &

nohup python main.py audit --auditors Phi --dataset cvefixes-100 --todo_code_par_dir data/cvefixes-100/add_attention_code/Phi/top0-100 --audit_output_dir results/cvefixes-100/add_attention_code/Phi/top0-100 --audit_mode rag > log/Phi.cvefixes-100.audit.log 2>&1  &

nohup python main.py audit --auditors CodeLlama --dataset cvefixes-100 --todo_code_par_dir data/cvefixes-100/add_attention_code/CodeLlama/top0-100 --audit_output_dir results/cvefixes-100/add_attention_code/CodeLlama/top0-100 --audit_mode rag > log/CodeLlama.cvefixes-100.audit.log 2>&1  &

nohup python main.py audit --auditors Gemma --dataset cvefixes-100 --todo_code_par_dir data/cvefixes-100/add_attention_code/Gemma/top0-100 --audit_output_dir results/cvefixes-100/add_attention_code/Gemma/top0-100 --audit_mode rag > log/Gemma.cvefixes-100.audit.log 2>&1  &

nohup python main.py audit --auditors MixtralExpert --dataset cvefixes-100 --todo_code_par_dir data/cvefixes-100/add_attention_code/MixtralExpert/top0-100 --audit_output_dir results/cvefixes-100/add_attention_code/MixtralExpert/top0-100 --audit_mode rag > log/MixtralExpert.cvefixes-100.audit.log 2>&1  &

### audit for baselines
#### solidity
nohup python main.py audit --auditors Mixtral Gemma --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/baselines --audit_output_dir results/smartbugs-collection/baselines/ --audit_mode rag > log/Mixtral-Gemma-baseline.audit.log 2>&1  &

nohup python main.py audit --auditors Gemma --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/baselines --audit_output_dir results/smartbugs-collection/baselines/ --audit_mode rag > log/Gemma-baseline.audit.log 2>&1  &


nohup python main.py audit --auditors MixtralExpert --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/baselines --audit_output_dir results/smartbugs-collection/baselines --audit_mode rag > log/MixtralExpert.baselines.audit.log 2>&1 &

nohup python main.py audit --auditors Phi --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/baselines --audit_output_dir results/smartbugs-collection/baselines --audit_mode rag > log/Phi.baselines.audit.log 2>&1 &

nohup python main.py audit --auditors CodeLlama --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/baselines --audit_output_dir results/smartbugs-collection/baselines --audit_mode rag > log/CodeLlama.baselines.audit.log 2>&1 &

nohup python main.py audit --auditors GPT4o --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/baselines --audit_output_dir results/smartbugs-collection/baselines --audit_mode rag > log/GPT4o.baselines.audit.log 2>&1 &
#### cpp
nohup python main.py audit --auditors Mixtral Phi CodeLlama --dataset big-vul-100 --todo_code_par_dir data/big-vul-100/baselines --audit_output_dir results/big-vul-100/baselines/ --audit_mode rag > log/Mixtral-Phi-CodeLlama-.cpp.baseline.audit.log 2>&1  &

nohup python main.py audit --auditors MixtralExpert Gemma --dataset big-vul-100 --todo_code_par_dir data/big-vul-100/baselines --audit_output_dir results/big-vul-100/baselines/ --audit_mode rag > log/MixtralExpert-Gemma-.cpp.baseline.audit.log 2>&1  &

#### python
nohup python main.py audit --auditors Mixtral Phi CodeLlama --dataset cvefixes-100 --todo_code_par_dir data/cvefixes-100/baselines --audit_output_dir results/cvefixes-100/baselines/ --audit_mode rag > log/Mixtral-Phi-CodeLlama-.py.baseline.audit.log 2>&1  &

nohup python main.py audit --auditors MixtralExpert Gemma --dataset cvefixes-100 --todo_code_par_dir data/cvefixes-100/baselines --audit_output_dir results/cvefixes-100/baselines/ --audit_mode rag > log/MixtralExpert-Gemma-.py.baseline.audit.log 2>&1  &


### top3 succ
#### yes or no
nohup python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_type/Mixtral --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Mixtral --audit_mode rag > log/Mixtral-top3succ.type.audit.log 2>&1  &

nohup python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_type/MixtralExpert --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_type/MixtralExpert --audit_mode rag > log/MixtralExpert-top3succ.type.audit.log 2>&1  &

nohup python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_type/Gemma --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Gemma --audit_mode rag > log/Gemma-top3succ.type.audit.log 2>&1  &

nohup python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_type/Phi --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Phi --audit_mode rag > log/Phi-top3succ.type.audit.log 2>&1  &

nohup python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_type/CodeLlama --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_type/CodeLlama --audit_mode rag > log/CodeLlama-top3succ.type.audit.log 2>&1  &

#### strict
nohup python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_strict/Mixtral --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_strict/Mixtral --audit_mode rag > log/Mixtral-top3succ.strict.audit.log 2>&1  &

nohup python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_strict/MixtralExpert --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_strict/MixtralExpert --audit_mode rag > log/MixtralExpert-top3succ.strict.audit.log 2>&1  &

nohup python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_strict/Gemma --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_strict/Gemma --audit_mode rag > log/Gemma-top3succ.strict.audit.log 2>&1  &

nohup python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_strict/Phi --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_strict/Phi --audit_mode rag > log/Phi-top3succ.strict.audit.log 2>&1  &

nohup python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_strict/CodeLlama --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_strict/CodeLlama --audit_mode rag > log/CodeLlama-top3succ.strict.audit.log 2>&1  &

#### join both type and yes or no
nohup bash -c '
python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_type/Mixtral --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Mixtral --audit_mode rag > log/Mixtral-top3succ.type.audit.log 2>&1  ;
python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_type/MixtralExpert --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_type/MixtralExpert --audit_mode rag > log/MixtralExpert-top3succ.type.audit.log 2>&1  ;
python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_type/Gemma --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Gemma --audit_mode rag > log/Gemma-top3succ.type.audit.log 2>&1  ;
python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_type/Phi --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Phi --audit_mode rag > log/Phi-top3succ.type.audit.log 2>&1 ;
python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_type/CodeLlama --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_type/CodeLlama --audit_mode rag > log/CodeLlama-top3succ.type.audit.log 2>&1 ;
python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/Mixtral --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/Mixtral --audit_mode rag > log/Mixtral-top3succ.yes_or_no.audit.log 2>&1  ;
python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/MixtralExpert --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/MixtralExpert --audit_mode rag > log/MixtralExpert-top3succ.yes_or_no.audit.log 2>&1  ;
python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/Gemma --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/Gemma --audit_mode rag > log/Gemma-top3succ.yes_or_no.audit.log 2>&1  ;
python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/Phi --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/Phi --audit_mode rag > log/Phi-top3succ.yes_or_no.audit.log 2>&1 ;
python main.py audit --auditors all --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/CodeLlama --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/CodeLlama --audit_mode rag > log/CodeLlama-top3succ.yes_or_no.audit.log 2>&1 
' &

#### join both type and yes or no -- GPT4o
nohup bash -c '
python main.py audit --auditors GPT4o --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_type/Mixtral --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Mixtral --audit_mode rag > log/Mixtral-top3succ.type.audit.log 2>&1  ;
python main.py audit --auditors GPT4o --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_type/MixtralExpert --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_type/MixtralExpert --audit_mode rag > log/MixtralExpert-top3succ.type.audit.log 2>&1  ;
python main.py audit --auditors GPT4o --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_type/Gemma --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Gemma --audit_mode rag > log/Gemma-top3succ.type.audit.log 2>&1  ;
python main.py audit --auditors GPT4o --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_type/Phi --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Phi --audit_mode rag > log/Phi-top3succ.type.audit.log 2>&1 ;
python main.py audit --auditors GPT4o --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_type/CodeLlama --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_type/CodeLlama --audit_mode rag > log/CodeLlama-top3succ.type.audit.log 2>&1 ;
python main.py audit --auditors GPT4o --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/Mixtral --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/Mixtral --audit_mode rag > log/Mixtral-top3succ.yes_or_no.audit.log 2>&1  ;
python main.py audit --auditors GPT4o --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/MixtralExpert --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/MixtralExpert --audit_mode rag > log/MixtralExpert-top3succ.yes_or_no.audit.log 2>&1  ;
python main.py audit --auditors GPT4o --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/Gemma --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/Gemma --audit_mode rag > log/Gemma-top3succ.yes_or_no.audit.log 2>&1  ;
python main.py audit --auditors GPT4o --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/Phi --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/Phi --audit_mode rag > log/Phi-top3succ.yes_or_no.audit.log 2>&1 ;
python main.py audit --auditors GPT4o --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/CodeLlama --audit_output_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/CodeLlama --audit_mode rag > log/CodeLlama-top3succ.yes_or_no.audit.log 2>&1 
' &

## 6 evaluate
### self top 100
#### solidity
python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors Mixtral --working_dir results/smartbugs-collection/add_attention_code/Mixtral/top0-100  --evaluate_mode type

python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors GPT4o Gemma Phi --working_dir results/smartbugs-collection/add_attention_code/Mixtral/top0-100  --evaluate_mode type

nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors MixtralExpert --working_dir results/smartbugs-collection/add_attention_code/MixtralExpert/top0-100  --evaluate_mode type > log/Phi.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors CodeLlama --working_dir results/smartbugs-collection/add_attention_code/CodeLlama/top0-100  --evaluate_mode type > log/CodeLlama.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors Gemma --working_dir results/smartbugs-collection/add_attention_code/Gemma/top0-100  --evaluate_mode type > log/Gemma.eval.log 2>&1 &


#### cpp
nohup python main.py evaluate --evaluator GPT4o --dataset big-vul-100 --auditors Mixtral --working_dir results/big-vul-100/add_attention_code/Mixtral/top0-100  --evaluate_mode type > log/Mixtral.cpp.self100.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset big-vul-100 --auditors Phi --working_dir results/big-vul-100/add_attention_code/Phi/top0-100  --evaluate_mode type > log/Phi.cpp.self100.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset big-vul-100 --auditors CodeLlama --working_dir results/big-vul-100/add_attention_code/CodeLlama/top0-100  --evaluate_mode type > log/CodeLlama.cpp.self100.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset big-vul-100 --auditors Gemma --working_dir results/big-vul-100/add_attention_code/Gemma/top0-100  --evaluate_mode type > log/Gemma.cpp.self100.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset big-vul-100 --auditors MixtralExpert --working_dir results/big-vul-100/add_attention_code/MixtralExpert/top0-100  --evaluate_mode type > log/MixtralExpert.cpp.self100.eval.log 2>&1 &


#### py

nohup python main.py evaluate --evaluator GPT4o --dataset cvefixes-100 --auditors Mixtral --working_dir results/cvefixes-100/add_attention_code/Mixtral/top0-100  --evaluate_mode type > log/Mixtral.py.self100.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset cvefixes-100 --auditors Phi --working_dir results/cvefixes-100/add_attention_code/Phi/top0-100  --evaluate_mode type > log/Phi.py.self100.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset cvefixes-100 --auditors CodeLlama --working_dir results/cvefixes-100/add_attention_code/CodeLlama/top0-100  --evaluate_mode type > log/CodeLlama.py.self100.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset cvefixes-100 --auditors Gemma --working_dir results/cvefixes-100/add_attention_code/Gemma/top0-100  --evaluate_mode type > log/Gemma.py.self100.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset cvefixes-100 --auditors MixtralExpert --working_dir results/cvefixes-100/add_attention_code/MixtralExpert/top0-100  --evaluate_mode type > log/MixtralExpert.py.self100.eval.log 2>&1 &


### baseline
#### solidity
nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors Mixtral MixtralExpert Phi Gemma CodeLlama --working_dir results/smartbugs-collection/baselines  --evaluate_mode type > log/baselines.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors GPT4o --working_dir results/smartbugs-collection/baselines  --evaluate_mode type > log/baselines.eval.log 2>&1 &

#### cpp
nohup python main.py evaluate --evaluator GPT4o --dataset big-vul-100 --auditors Mixtral Phi CodeLlama --working_dir results/big-vul-100/baselines  --evaluate_mode type > log/Mixtral-Phi-CodeLlama.cpp.baselines.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset big-vul-100 --auditors MixtralExpert Gemma --working_dir results/big-vul-100/baselines  --evaluate_mode type > log/MixtralExpert-Gemma.cpp.baselines.eval.log 2>&1 &

#### py
nohup python main.py evaluate --evaluator GPT4o --dataset cvefixes-100 --auditors Mixtral Phi CodeLlama --working_dir results/cvefixes-100/baselines  --evaluate_mode type > log/Mixtral-Phi-CodeLlama.py.baselines.eval.log 2>&1 &

todo
nohup python main.py evaluate --evaluator GPT4o --dataset cvefixes-100 --auditors MixtralExpert Gemma --working_dir results/cvefixes-100/baselines  --evaluate_mode type > log/MixtralExpert-Gemma.py.baselines.eval.log 2>&1 &

join
nohup bash -c 'python main.py evaluate --evaluator GPT4o --dataset big-vul-100 --auditors Mixtral --working_dir results/big-vul-100/add_attention_code/Mixtral/top0-100  --evaluate_mode type > log/Mixtral.cpp.self100.eval.log 2>&1 && python main.py evaluate --evaluator GPT4o --dataset big-vul-100 --auditors Phi --working_dir results/big-vul-100/add_attention_code/Phi/top0-100  --evaluate_mode type > log/Phi.cpp.self100.eval.log 2>&1 && python main.py evaluate --evaluator GPT4o --dataset big-vul-100 --auditors CodeLlama --working_dir results/big-vul-100/add_attention_code/CodeLlama/top0-100  --evaluate_mode type > log/CodeLlama.cpp.self100.eval.log 2>&1 && python main.py evaluate --evaluator GPT4o --dataset cvefixes-100 --auditors Mixtral --working_dir results/cvefixes-100/add_attention_code/Mixtral/top0-100  --evaluate_mode type > log/Mixtral.py.self100.eval.log 2>&1 && nohup python main.py evaluate --evaluator GPT4o --dataset cvefixes-100 --auditors Phi --working_dir results/cvefixes-100/add_attention_code/Phi/top0-100  --evaluate_mode type > log/Phi.py.self100.eval.log 2>&1 && python main.py evaluate --evaluator GPT4o --dataset cvefixes-100 --auditors CodeLlama --working_dir results/cvefixes-100/add_attention_code/CodeLlama/top0-100  --evaluate_mode type > log/CodeLlama.py.self100.eval.log 2>&1 && python main.py evaluate --evaluator GPT4o --dataset big-vul-100 --auditors Mixtral Phi CodeLlama --working_dir results/big-vul-100/baselines  --evaluate_mode type > log/Mixtral-Phi-CodeLlama.cpp.baselines.eval.log 2>&1 && python main.py evaluate --evaluator GPT4o --dataset cvefixes-100 --auditors Mixtral Phi CodeLlama --working_dir results/cvefixes-100/baselines  --evaluate_mode type > log/Mixtral-Phi-CodeLlama.py.baselines.eval.log 2>&1' &

### top3 succ
#### sol
##### type
nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Mixtral  --evaluate_mode type > log/Mixtral-top3succ.type.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/MixtralExpert  --evaluate_mode type > log/MixtralExpert-top3succ.type.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/CodeLlama  --evaluate_mode type > log/CodeLlama-top3succ.type.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Gemma  --evaluate_mode type > log/Gemma-top3succ.type.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Phi  --evaluate_mode type > log/Phi-top3succ.type.eval.log 2>&1 &

##### strict
nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_strict/Mixtral  --evaluate_mode type > log/Mixtral-top3succ.strict.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_strict/MixtralExpert  --evaluate_mode type > log/MixtralExpert-top3succ.strict.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_strict/CodeLlama  --evaluate_mode type > log/CodeLlama-top3succ.strict.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_strict/Gemma  --evaluate_mode type > log/Gemma-top3succ.strict.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_strict/Phi  --evaluate_mode type > log/Phi-top3succ.strict.eval.log 2>&1 &

##### batch
nohup bash -c 'python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Gemma  --evaluate_mode type && python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Phi  --evaluate_mode type > log/Phi-Gemma-top3succ.type.eval.log 2>&1' &


join both type and yes or no
nohup bash -c '
python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Mixtral  --evaluate_mode type > log/Mixtral-top3succ.type.eval.log 2>&1 ;
python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/MixtralExpert  --evaluate_mode type > log/MixtralExpert-top3succ.type.eval.log 2>&1 ;
python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/CodeLlama  --evaluate_mode type > log/CodeLlama-top3succ.type.eval.log 2>&1 ;
python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Gemma  --evaluate_mode type > log/Gemma-top3succ.type.eval.log 2>&1 ;
python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Phi  --evaluate_mode type > log/Phi-top3succ.type.eval.log 2>&1 ;
python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/Mixtral  --evaluate_mode type > log/Mixtral-top3succ.yes_or_no.eval.log 2>&1 ;
python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/MixtralExpert  --evaluate_mode type > log/MixtralExpert-top3succ.yes_or_no.eval.log 2>&1 ;
python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/CodeLlama  --evaluate_mode type > log/CodeLlama-top3succ.yes_or_no.eval.log 2>&1 ;
python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/Gemma  --evaluate_mode type > log/Gemma-top3succ.yes_or_no.eval.log 2>&1 ;
python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors all --working_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/Phi  --evaluate_mode type > log/Phi-top3succ.yes_or_no.eval.log 2>&1 
' &

#### cpp
todo select top3

#### py
todo select top3



### fix phi audit
#### sol self 100 (phi, mixtral)
nohup bash -c 'python main.py audit --auditors Phi --dataset smartbugs-collection --todo_code_par_dir data/smartbugs-collection/add_attention_code/Mixtral/top0-100 --audit_output_dir results/smartbugs-collection/add_attention_code/Mixtral/top0-100 --audit_mode rag > fixPhi.sol.mixtral100.audit.log 2>&1 && python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors Phi --working_dir results/smartbugs-collection/add_attention_code/Mixtral/top0-100  --evaluate_mode type > log/fixPhi.sol.mixtral100.eval.log 2>&1' &


nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors Phi --working_dir results/smartbugs-collection/add_attention_code/Mixtral/top0-100  --evaluate_mode type > log/fixPhi.sol.mixtral100.eval.log 2>&1 &

nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors Phi --working_dir results/smartbugs-collection/add_attention_code/Phi/top0-100  --evaluate_mode type > log/fixPhi.sol.self100.eval.log 2>&1 &

#### baseline
nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors Phi --working_dir results/smartbugs-collection/baselines  --evaluate_mode type > log/fixPhi.sol.baselines.eval.log 2>&1 &

join
nohup bash -c 'nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors Phi --working_dir results/smartbugs-collection/add_attention_code/Phi/top0-100  --evaluate_mode type > log/fixPhi.sol.self100.eval.log 2>&1 && nohup python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors Phi --working_dir results/smartbugs-collection/baselines  --evaluate_mode type > log/fixPhi.baselines.eval.log 2>&1 ' &

#### top3
nohup bash -c 'python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors Phi --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Gemma  --evaluate_mode type > log/fixPhi-top3succ.type.eval.log 2>&1 && python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors Phi --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Phi  --evaluate_mode type >> log/fixPhi-top3succ.type.eval.log 2>&1 && python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors Phi --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Mixtral --evaluate_mode type >> log/fixPhi-top3succ.type.eval.log 2>&1 && python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors Phi --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/MixtralExpert  --evaluate_mode type >> log/fixPhi-top3succ.type.eval.log 2>&1 && python main.py evaluate --evaluator GPT4o --dataset smartbugs-collection --auditors Phi --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/CodeLlama  --evaluate_mode type >> log/fixPhi-top3succ.type.eval.log 2>&1' &



## 7 count blind
test for vuln-10 case study
python main.py count_blind --working_dir results/vuln-10/add_attention_code/Mixtral/top0-100 --evaluate_modes type --judge_mode all


### top100
#### sol
python main.py count_blind --working_dir results/smartbugs-collection/add_attention_code/Mixtral/top0-100 --evaluate_modes type --judge_mode all

python main.py count_blind --working_dir results/smartbugs-collection/add_attention_code/MixtralExpert/top0-100 --evaluate_modes type

python main.py count_blind --working_dir results/smartbugs-collection/add_attention_code/Gemma/top0-100 --evaluate_modes type

python main.py count_blind --working_dir results/smartbugs-collection/add_attention_code/CodeLlama/top0-100 --evaluate_modes type

python main.py count_blind --working_dir results/smartbugs-collection/add_attention_code/Phi/top0-100 --evaluate_modes type

#### cpp
python main.py count_blind --working_dir results/big-vul-100/add_attention_code/Mixtral/top0-100 --evaluate_modes type

python main.py count_blind --working_dir results/big-vul-100/add_attention_code/CodeLlama/top0-100 --evaluate_modes type

python main.py count_blind --working_dir results/big-vul-100/add_attention_code/Phi/top0-100 --evaluate_modes type

python main.py count_blind --working_dir results/big-vul-100/add_attention_code/Gemma/top0-100 --evaluate_modes type

python main.py count_blind --working_dir results/big-vul-100/add_attention_code/MixtralExpert/top0-100 --evaluate_modes type


#### py
python main.py count_blind --working_dir results/cvefixes-100/add_attention_code/Mixtral/top0-100 --evaluate_modes type

python main.py count_blind --working_dir results/cvefixes-100/add_attention_code/CodeLlama/top0-100 --evaluate_modes type

python main.py count_blind --working_dir results/cvefixes-100/add_attention_code/Phi/top0-100 --evaluate_modes type

python main.py count_blind --working_dir results/cvefixes-100/add_attention_code/Gemma/top0-100 --evaluate_modes type

python main.py count_blind --working_dir results/cvefixes-100/add_attention_code/MixtralExpert/top0-100 --evaluate_modes type


### baseline
#### sol
python main.py count_blind --working_dir results/smartbugs-collection/baselines --evaluate_modes type

python main.py count_blind --working_dir results/big-vul-100/baselines --evaluate_modes type

python main.py count_blind --working_dir results/cvefixes-100/baselines --evaluate_modes type


### top3 succ
#### sol
python main.py count_blind --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Mixtral --evaluate_modes type
python main.py count_blind --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/MixtralExpert --evaluate_modes type
python main.py count_blind --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Gemma --evaluate_modes type
python main.py count_blind --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/CodeLlama --evaluate_modes type
python main.py count_blind --working_dir results/smartbugs-collection/top3_succ_of_whitebox_type/Phi --evaluate_modes type

python main.py count_blind --working_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/Mixtral --evaluate_modes type
python main.py count_blind --working_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/MixtralExpert --evaluate_modes type
python main.py count_blind --working_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/Gemma --evaluate_modes type
python main.py count_blind --working_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/CodeLlama --evaluate_modes type
python main.py count_blind --working_dir results/smartbugs-collection/top3_succ_of_whitebox_yes_or_no/Phi --evaluate_modes type

python main.py count_blind --working_dir results/smartbugs-collection/top3_succ_of_whitebox_strict/Mixtral --evaluate_modes type
python main.py count_blind --working_dir results/smartbugs-collection/top3_succ_of_whitebox_strict/MixtralExpert --evaluate_modes type
python main.py count_blind --working_dir results/smartbugs-collection/top3_succ_of_whitebox_strict/Gemma --evaluate_modes type
python main.py count_blind --working_dir results/smartbugs-collection/top3_succ_of_whitebox_strict/CodeLlama --evaluate_modes type
python main.py count_blind --working_dir results/smartbugs-collection/top3_succ_of_whitebox_strict/Phi --evaluate_modes type

## 8. draw line
### top100
#### sol
python main.py draw_line --working_dir results/smartbugs-collection/add_attention_code/Mixtral/top0-100 --rank_path function_selection/messiq_dataset/Mixtral/sum/100/summary.json --evaluate_modes type

python main.py draw_line --working_dir results/smartbugs-collection/add_attention_code/MixtralExpert/top0-100 --rank_path function_selection/messiq_dataset/MixtralExpert/sum/100/summary.json --evaluate_modes type

python main.py draw_line --working_dir results/smartbugs-collection/add_attention_code/CodeLlama/top0-100 --rank_path function_selection/messiq_dataset/CodeLlama/sum/100/summary.json --evaluate_modes type

python main.py draw_line --working_dir results/smartbugs-collection/add_attention_code/Gemma/top0-100 --rank_path function_selection/messiq_dataset/Gemma/sum/100/summary.json --evaluate_modes type

python main.py draw_line --working_dir results/smartbugs-collection/add_attention_code/Phi/top0-100 --rank_path function_selection/messiq_dataset/Phi/sum/100/summary.json --evaluate_modes type

#### cpp
python main.py draw_line --working_dir results/big-vul-100/add_attention_code/Mixtral/top0-100 --rank_path function_selection/leetcode_cpp/Mixtral/sum/100/summary.json --evaluate_modes type

python main.py draw_line --working_dir results/big-vul-100/add_attention_code/Phi/top0-100 --rank_path function_selection/leetcode_cpp/Phi/sum/100/summary.json --evaluate_modes type

python main.py draw_line --working_dir results/big-vul-100/add_attention_code/CodeLlama/top0-100 --rank_path function_selection/leetcode_cpp/CodeLlama/sum/100/summary.json --evaluate_modes type

#### py
python main.py draw_line --working_dir results/cvefixes-100/add_attention_code/Mixtral/top0-100 --rank_path function_selection/leetcode_python/Mixtral/sum/100/summary.json --evaluate_modes type

python main.py draw_line --working_dir results/cvefixes-100/add_attention_code/Phi/top0-100 --rank_path function_selection/leetcode_python/Phi/sum/100/summary.json --evaluate_modes type

python main.py draw_line --working_dir results/cvefixes-100/add_attention_code/CodeLlama/top0-100 --rank_path function_selection/leetcode_python/CodeLlama/sum/100/summary.json --evaluate_modes type

## 9. count time
python main.py count_time --phase auditor --auditors all --working_dir results/smartbugs-collection/add_attention_code/Mixtral/top0-100 --evaluate_modes type

python main.py count_time --phase evaluator --auditors all --working_dir results/smartbugs-collection/add_attention_code/Mixtral/top0-100 --evaluate_modes type

## 10. my topN on you

python main.py me_topN_on_you --N 1 --me Mixtral --working_dir results/smartbugs-collection/add_attention_code/Mixtral/top0-100 --evaluate_modes type

## 13. code similarity
nohup python c13_code_similarity.py > log/code_similarity 2>&1 &


## 18. audit malware
nohup python main.py audit_malware --auditors Mixtral --dataset malware-10 --todo_code_par_dir data/malware-10/add_attention_code --audit_output_dir results/malware-10/add_attention_code --audit_mode rag > log/Mixtral.malware-10.audit.log 2>&1  &

nohup python main.py audit_malware --auditors GPT4o --dataset malware-10 --todo_code_par_dir data/malware-10/add_attention_code --audit_output_dir results/malware-10/add_attention_code --audit_mode rag > log/GPT4o.malware-10.audit.log 2>&1  &