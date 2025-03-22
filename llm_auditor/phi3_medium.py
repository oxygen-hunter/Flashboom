from transformers import AutoTokenizer, AutoModelForCausalLM, BitsAndBytesConfig
import torch, os
from llm_auditor.base_auditor import BaseAuditor
from transformers.utils import is_flash_attn_2_available

class Phi(BaseAuditor):
    def __init__(self, max_new_tokens=300, use_flash_attn=False, **kwargs):
        super().__init__(
            max_new_tokens=max_new_tokens,
            begin_token="[INST]",
            end_token="[/INST]",
            support_system_prompt = True,
            linebreak='<0x0A>',
            **kwargs
        )
        self.model_id = "microsoft/Phi-3-medium-4k-instruct"

        quantization_config = BitsAndBytesConfig(
            load_in_4bit=True,
            bnb_4bit_use_double_quant=True,
            bnb_4bit_quant_type="nf4",
            bnb_4bit_compute_dtype=torch.bfloat16,
        )

        local_model_dir = os.path.expanduser('~/.cache/huggingface/hub/models--microsoft--Phi-3-medium-4k-instruct/snapshots/ae004ae82eb6eddc32906dfacb1d6dfea8f91996')

        if use_flash_attn:
            # self.model = AutoModelForCausalLM.from_pretrained(
            #     self.model_id,
            #     quantization_config=quantization_config,
            #     device_map="auto",
            #     torch_dtype="auto",
            #     trust_remote_code=True,
            #     attn_implementation="flash_attention_2",
            # )
            self.model = AutoModelForCausalLM.from_pretrained(
                local_model_dir,
                quantization_config=quantization_config,
                device_map="auto",
                torch_dtype="auto",
                trust_remote_code=True,
                attn_implementation="flash_attention_2",
            )
        else:
            # self.model = AutoModelForCausalLM.from_pretrained(
            #     self.model_id,
            #     quantization_config=quantization_config,
            #     device_map="auto"
            # )
            self.model = AutoModelForCausalLM.from_pretrained(
                local_model_dir,
                quantization_config=quantization_config,
                device_map="auto"
            )

        # self.tokenizer = AutoTokenizer.from_pretrained(
        #     self.model_id
        # )
        self.tokenizer = AutoTokenizer.from_pretrained(
            local_model_dir
        )

        print("flash attn available? ", is_flash_attn_2_available())