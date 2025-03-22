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


    bool confusingNumber(int N) {
        static const unordered_map<char, char> lookup = 
            {{'0', '0'}, {'1', '1'}, {'6', '9'},
             {'8', '8'}, {'9', '6'}};
 
        const auto& S = to_string(N);
        for (int i = 0; i < S.length(); ++i) {
            if (!lookup.count(S[i])) {
                return false;
            }
        }
        for (int i = 0; i < (S.length() + 1) / 2; ++i) {
            if (S[i] != lookup.at(S[S.length() - 1 - i])) {
                return true;
            }
        }
        return false;
    }


