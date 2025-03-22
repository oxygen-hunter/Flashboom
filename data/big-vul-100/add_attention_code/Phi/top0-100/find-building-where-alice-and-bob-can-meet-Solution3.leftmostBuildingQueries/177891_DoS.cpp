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

    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        vector<int> result(size(queries), -1);
        vector<vector<pair<int, int>>> qs(size(heights));
        for (int i = 0; i < size(queries); ++i) {
            int a = queries[i][0], b = queries[i][1];
            if (a > b) {
                swap(a, b);
            }
            if (a == b || heights[a] < heights[b]) {
                result[i] = b;
            } else {
                qs[b].emplace_back(heights[a], i);
            }
        }
        vector<pair<int, int>> stk;
        const auto& binary_search_right = [&](int left, int right, const auto& check) {
            while (left <= right) {
                const int mid = left + (right - left) / 2;
                if (!check(mid)) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return right;
        };

        for (int b = size(heights) - 1; b >= 0; --b) {
            while (!empty(stk) && stk.back().first <= heights[b]) {
                stk.pop_back();
            }
            stk.emplace_back(heights[b], b);
            for (const auto& [ha, i] : qs[b]) {
                const int j = binary_search_right(0, size(stk) - 1, [&, &ha = ha](int x) {
                    return stk[x].first > ha;
                });
                if (j >= 0) {
                    result[i] = stk[j].second;
                }
            }
        }
        return result;
    }

