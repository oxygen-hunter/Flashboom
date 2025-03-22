# Requires transformers>=4.36.0

import torch.nn.functional as F
from transformers import AutoModel, AutoTokenizer
import os


class GteLargeEn:
    def __init__(self):
        # model_path = 'Alibaba-NLP/gte-large-en-v1.5'
        # self.tokenizer = AutoTokenizer.from_pretrained(model_path)
        # self.model = AutoModel.from_pretrained(model_path, trust_remote_code=True)

        local_model_dir = os.path.expanduser('~/.cache/huggingface/hub/models--Alibaba-NLP--gte-large-en-v1.5/snapshots/104333d6af6f97649377c2afbde10a7704870c7b')

        self.model = AutoModel.from_pretrained(
            local_model_dir,
            trust_remote_code=True
        )

        self.tokenizer = AutoTokenizer.from_pretrained(
            local_model_dir
        )

    def similarity(self, input_texts:list)->list:
        # Tokenize the input texts
        batch_dict = self.tokenizer(input_texts, max_length=8192, padding=True, truncation=True, return_tensors='pt')

        outputs = self.model(**batch_dict)
        embeddings = outputs.last_hidden_state[:, 0]
        
        # (Optionally) normalize embeddings
        embeddings = F.normalize(embeddings, p=2, dim=1)
        scores = (embeddings[:1] @ embeddings[1:].T)
        return scores.tolist()[0]
    
