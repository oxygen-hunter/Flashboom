static RSA_PSS_PARAMS *rsa_pss_decode(const X509_ALGOR *alg,
                                      X509_ALGOR **pmaskHash)
{
    const unsigned char *p;
    int plen;
    RSA_PSS_PARAMS *pss;

    *pmaskHash = NULL;

    if (!alg->parameter || alg->parameter->type != V_ASN1_SEQUENCE)
        return NULL;
    p = alg->parameter->value.sequence->data;
    plen = alg->parameter->value.sequence->length;
    pss = d2i_RSA_PSS_PARAMS(NULL, &p, plen);

    if (!pss)
        return NULL;

     if (pss->maskGenAlgorithm) {
         ASN1_TYPE *param = pss->maskGenAlgorithm->parameter;
         if (OBJ_obj2nid(pss->maskGenAlgorithm->algorithm) == NID_mgf1
            && param->type == V_ASN1_SEQUENCE) {
             p = param->value.sequence->data;
             plen = param->value.sequence->length;
             *pmaskHash = d2i_X509_ALGOR(NULL, &p, plen);
        }
    }

    return pss;
}


    int stoneGameVI(vector<int>& aliceValues, vector<int>& bobValues) {
        vector<vector<int>> sorted_vals;
        vector<int> result(2);
        for (int i = 0; i < size(aliceValues); ++i) {
            sorted_vals.push_back({aliceValues[i] + bobValues[i],
                                   aliceValues[i], bobValues[i]});
        }
        sort(begin(sorted_vals), end(sorted_vals), greater<vector<int>>());
        for (int i = 0; i < size(sorted_vals); ++i) {
            result[i % 2] += sorted_vals[i][1 + i % 2];
        }
        return (result[0] == result[1]) ? 0 : (result[0] > result[1]) ? 1 : -1;
    }


