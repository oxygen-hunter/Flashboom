
from llm_auditor.gpt4 import GPT4o
from llm_auditor.codellama_7b import CodeLlama
from llm_auditor.gemma_2b import Gemma
from llm_auditor.mixtral_7b import Mixtral
from llm_auditor.mixtral_8x7b import MixtralExpert
from llm_auditor.phi3_medium import Phi

def init_model(model_name, max_new_tokens, use_flash_attn=False):
    model = None
    match model_name:
        case 'GPT4o':    
            model = GPT4o()
        case 'CodeLlama':
            model = CodeLlama(max_new_tokens=max_new_tokens)
        case 'Gemma':
            model = Gemma(max_new_tokens=max_new_tokens)
        case 'Mixtral':
            model = Mixtral(max_new_tokens=max_new_tokens)
        case 'MixtralExpert':
            model = MixtralExpert(max_new_tokens=max_new_tokens)
        case 'Phi':
            model = Phi(max_new_tokens=max_new_tokens, use_flash_attn=use_flash_attn)
    return model