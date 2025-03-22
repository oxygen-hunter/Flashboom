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


    string originalDigits(string s) {
        const vector<string> numbers{"zero", "one", "two", "three",
                                     "four", "five", "six", "seven",
                                     "eight", "nine"};
        vector<vector<int>> cnts(numbers.size(), vector<int>(26));
        for (int i = 0; i < numbers.size(); ++i) {
            for (const auto& c : numbers[i]) {
                ++cnts[i][c - 'a'];
            }
        }
        
        // The order for greedy method.
        vector<int> order{0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
        
        // The unique char in the order.
        vector<char> unique_chars{'z', 'o', 'w', 't', 'u', 'f', 'x', 's', 'g', 'n'};
        vector<int> cnt(26);
        for (const auto& c : s) {
            ++cnt[c - 'a'];
        }

        string result;
        for (const auto& i : order) {
            while (cnt[unique_chars[i] - 'a'] > 0) {
                for (int j = 0; j < cnt.size(); ++j) {
                    cnt[j] -= cnts[i][j];
                }
                result.push_back(i + '0');
            }
        }
        sort(result.begin(), result.end());
        return result;
    }


