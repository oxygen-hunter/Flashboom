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


    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) {
        const auto& count = [](int64_t l) {
            return (l + 1) * l / 2;
        };

        vector<int64_t> prefix(size(s) + 1);
        vector<int> lookup(size(s), -1);
        for (int right = 0, left = 0, cnt = 0; right < size(s); ++right) {
            cnt += s[right] == '1' ? 1 : 0;
            while (!(cnt <= k || (right - left + 1) - cnt <= k)) {
                cnt -= s[left++] == '1' ? 1 : 0;
            }
            prefix[right + 1] = prefix[right] + (right - left + 1);
            lookup[left] = right;
        }
        assert(lookup[0] != -1);
        for (int i = 0; i + 1 < size(s); ++i) {
            if (lookup[i + 1] == -1) {
                lookup[i + 1] = lookup[i];
            }
        }
        vector<long long> result(size(queries));
        for (int i = 0; i < size(queries); ++i) {
            const int left = queries[i][0], right = queries[i][1];
            const int new_right = min(lookup[left], right);
            result[i] = count(new_right - left + 1) + (prefix[right + 1] - prefix[new_right + 1]);
        }
        return result;
    }


