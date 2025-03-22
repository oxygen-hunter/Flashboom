import ast

'''
just evaluate whether predicted report contains vuln in correct report or not
'''
def evaluate_vuln_report_1_to_2(model, predicted_report, correct_report):
    system_prompt = \
'''
You are an intelligent chatbot designed for evaluating the factual accuracy of vulnerability report for Solidity code.
Your task is to compare the predicted report with the correct report and determine whether the predicted report contains the correct vulnerability/attack/security issues/security risks. Here is how you can accomplish the task:
------
##INSTRUCTIONS:
- Focus on vulnerability/attack/security issue/security risk mentioned in correct report, and verify whether these elements exist in predicted report.
- Consider synonyms or paraphrases as valid matches.
'''
    user_prompt = \
f'''
Please evaluate the following predicted report for Solidity code vulnerability detection:

Correct report: {correct_report}

Predicted report: {predicted_report}

'''+\
'''
The correct report contains one and only one vulnerability, and the predicted report contains 0, 1 or more vulnerability.
Provide your evaluation only as a score, where the score is an integer value between 0 and 2. The meaning of value is as follows:
- 1 means the vulnerability mentioned in correct report doesn't exists in predicted report. e.g. correct report contains vulnerability A, but predicted report contains vulnerability B and C.
- 2 means the vulnerability mentioned in correct report exists in predicted report. e.g. correct report contains vulnerability A, and predicted report contains vulnerability A and D.
- 0 means you meet some unexpected circumstances not mentioned above.

Please generate the response in the form of Python dictionary string with keys 'score', where its value is the factual accuracy score in INTEGER, not STRING.
DO NOT PROVIDE ANY OTHER OUTPUT TEXT OR EXPLANATION. Only provide the Python dictionary string. DO NOT WRAP IT like python```{''score': 2}```.

For example, your response should look like this: {'score': 2}."
'''
    (results, input_token_length, output_token_length, inference_time) = model.inference(system_prompt, user_prompt)

    runtime_info = {
        'input_token_length': input_token_length,
        'output_token_length': output_token_length,
        'inference_time': inference_time
    }

    response_dict = ast.literal_eval(results)
    if type(response_dict) == dict and 'score' in response_dict:
        return response_dict['score'], runtime_info
    else:
        return -1, runtime_info
