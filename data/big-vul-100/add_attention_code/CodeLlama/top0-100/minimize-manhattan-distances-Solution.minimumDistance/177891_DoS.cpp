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


    int minimumDistance(vector<vector<int>>& points) {
        const auto& max_distance = [&](int exclude) {
            static const int POS_INF = numeric_limits<int>::max();
            static const int NEG_INF = numeric_limits<int>::min();
    
            pair<int, int> max_sum = {NEG_INF, -1};
            pair<int, int> min_sum = {POS_INF, -1};
            pair<int, int> max_diff = {NEG_INF, -1};
            pair<int, int> min_diff = {POS_INF, -1};
            for (int i = 0; i < size(points); ++i) {
                if (i == exclude) {
                    continue;
                }
                const int x = points[i][0], y = points[i][1];
                max_sum = max(max_sum, {x + y, i});
                min_sum = min(min_sum, {x + y, i});
                max_diff = max(max_diff, {x - y, i});
                min_diff = min(min_diff, {x - y, i});
            }
            return max(tuple{max_sum.first - min_sum.first, max_sum.second, min_sum.second},
                       tuple{max_diff.first - min_diff.first, max_diff.second, min_diff.second});
        };
    
        const auto& [_, i, j] = max_distance(-1);
        return min(get<0>(max_distance(i)), get<0>(max_distance(j)));
    }


