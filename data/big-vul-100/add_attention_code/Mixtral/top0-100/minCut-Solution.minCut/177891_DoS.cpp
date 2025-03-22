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

        int minCut(string s) {
            const int n = s.size();
            vector<vector<bool> > p(n, vector<bool>(n, false)); // p[i][j]: range [i, j] is a palindrome paritioning of s
            vector<int> f(n + 1, 0); // f[i]: minimum cuts in range [i, n - 1]

            for(int i = 0; i <= n; ++i) {
                f[i] = n - 1 - i;    // initialize f[i] to the max cuts
            }

            for (int i = n - 1; i >= 0; --i) {
                for (int j = i; j < n; ++j) {
                    // [i, j] is palindrome if only if s[i] equals to s[j] and [i + 1, j - 1] is palindrome too
                    if(s[i] == s[j] && ((j - i < 2) || p[i + 1][j - 1])) {
                        p[i][j] = true;
                        f[i] = min(f[i], f[j + 1] + 1);  // f[i] = min(f[j + 1] + 1) for each i <= j <= n - 1
                    }
                }   
            }

            return f[0];
        }

