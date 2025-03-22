import ast
import re

def evaluate_vuln_report_1_to_4(model, predicted_report, correct_report):
    system_prompt = \
'''
You are an intelligent chatbot designed for evaluating the factual accuracy of vulnerability report for source code (source code language: Solidity/C++/Python).
Your task is to compare the predicted report with the correct report and determine whether the predicted report contains the correct vulnerability/attack/security issues/security risks. Here is how you can accomplish the task:
------
##INSTRUCTIONS:
- Focus on vulnerability/attack/security issue/security risk mentioned in correct report, and verify whether these elements exist in predicted report.
- Focus on any CVE-ID/CWE-ID and its explanation in correct report, and verify whether these elements exist in predicted report.
- Focus on the consistency of the two report. For example 1, if the predicted report doesn't mention the specific name of vulnerability, instead, claiming that it contains a similar or same vulnerability compared to the correct report, that is also ok. For example 2, if the predicted report doesn't mention the exactly CVE/CWE-ID, but it mentions a description that matches the CVE/CWE-ID in correct report, that is also ok.
- Consider synonyms or paraphrases as valid matches.
'''
    user_prompt = \
f'''
Please evaluate the following predicted report for source code vulnerability detection:

Correct report: {correct_report}

Predicted report: {predicted_report}

'''+\
'''
Provide your evaluation only as a score, where the score is an integer value between 0 and 4. The meaning of value is as follows:
- 1 means predicted report doesn't contain any vulnerability.
- 2 means predicted report doesn't contain any vulnerability mentioned in correct report, but contain some other vulnerabilities. e.g. correct report contains vulnerability A, predicted report contains vulnerability B C D.
- 3 means predicted report contains and only contains the vulnerability mentioned in correct report. e.g. correct report contains vulnerability A, predicted report contains vulnerability A, or claiming that it contains a similar or same vulnerability without mentioning the name of A.
- 4 means predicted report contains the vulnerability mentioned in correct report, but also contains some other vulnerabilities. e.g. correct report contains vulnerability A, predicted report contains vulnerability A B C D.
- 0 means you meet some unexpected circumstances not mentioned above.

Please generate the response in the form of Python dictionary string with keys 'score', where its value is the factual accuracy score in INTEGER, not STRING.
DO NOT PROVIDE ANY OTHER OUTPUT TEXT OR EXPLANATION. Only provide the Python dictionary string. DO NOT WRAP IT like python```{'score': 2}``` or ```{'score': 2}```.

For example, your response should look like this: {'score': 2}.
'''

    #print(user_prompt) 
    #print('---------')
    

    (results, input_token_num, output_token_num, inference_time) = model.inference(system_prompt, user_prompt)
    runtime_info = {
        'input_token_num': input_token_num,
        'output_token_num': output_token_num,
        'inference_time': inference_time
    }

    def parse_score(string):
        # regrex {'score': N}
        match1 = re.match(r"\{'score': (\d+)\}", string)
        match2 = re.match(r'\{"score": (\d+)\}', string)
        if match1:
            # succ: N
            return int(match1.group(1))
        elif match2:
            return int(match2.group(1))
        else:
            # fail: -1
            print('parse fail:', results)
            return -1
        
    return parse_score(results), runtime_info