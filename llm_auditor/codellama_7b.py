from transformers import AutoTokenizer, AutoModelForCausalLM, BitsAndBytesConfig
import torch, os
from llm_auditor.base_auditor import BaseAuditor


class CodeLlama(BaseAuditor):
    def __init__(self, max_new_tokens=300, **kwargs):
        super().__init__(
            max_new_tokens=max_new_tokens,
            begin_token="[INST]",
            end_token="[/INST]",
            support_system_prompt = True,
            linebreak = '<0x0A>',
            **kwargs
        )
        self.model_id = "codellama/CodeLlama-7b-Instruct-hf"

        quantization_config = BitsAndBytesConfig(
            load_in_4bit=True,
            bnb_4bit_use_double_quant=True,
            bnb_4bit_quant_type="nf4",
            bnb_4bit_compute_dtype=torch.bfloat16,
        )
        # self.model = AutoModelForCausalLM.from_pretrained(
        #     self.model_id,
        #     quantization_config=quantization_config,
        #     device_map="auto",
        # )

        # self.tokenizer = AutoTokenizer.from_pretrained(
        #     self.model_id
        # )

        local_model_dir = os.path.expanduser('~/.cache/huggingface/hub/models--codellama--CodeLlama-7b-Instruct-hf/snapshots/22cb240e0292b0b5ab4c17ccd97aa3a2f799cbed')

        self.model = AutoModelForCausalLM.from_pretrained(
            local_model_dir,
            quantization_config=quantization_config,
            device_map="auto"
        )

        self.tokenizer = AutoTokenizer.from_pretrained(
            local_model_dir
        )
