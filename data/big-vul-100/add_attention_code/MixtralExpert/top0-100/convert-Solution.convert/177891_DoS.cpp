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


        string convert(string s, int nRows) {
            vector<string> row(nRows);
            string ans;
            int cnt = 0;

            if(nRows == 1)
                return s;

            for(auto c : s) {
                if(cnt < nRows) {
                    row[cnt].push_back(c);
                }
                else {
                    row[2 * nRows - 2 - cnt].push_back(c);
                }

                cnt = (cnt + 1) % (2 * nRows - 2);
            }

            for(auto s : row) {
                ans.append(s);
            }

            return ans;
        }


