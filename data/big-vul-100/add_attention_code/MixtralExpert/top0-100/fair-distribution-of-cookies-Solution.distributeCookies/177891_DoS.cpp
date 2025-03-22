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


    int distributeCookies(vector<int>& cookies, int k) {
        vector<int> total(1 << size(cookies));
        for (int mask = 0; mask < (1 << size(cookies)); ++mask) {
            for (int i = 0; i < size(cookies); ++i) {
                if (mask & (1 << i)) {
                    total[mask] += cookies[i];
                }
            }
        }
        vector<vector<int>> dp(2, vector<int>(1 << size(cookies), numeric_limits<int>::max()));
        dp[0][0] = 0;
        for (int i = 0; i < k; ++i) {
            for (int mask = 0; mask < (1 << size(cookies)); ++mask) {
                for (int submask = mask; submask; submask = (submask - 1) & mask) {
                    dp[(i + 1) % 2][mask] = min(dp[(i + 1) % 2][mask], max(total[submask], dp[i % 2][mask ^ submask]));
                }
            }
        }
        return dp[k % 2].back();
    }   


