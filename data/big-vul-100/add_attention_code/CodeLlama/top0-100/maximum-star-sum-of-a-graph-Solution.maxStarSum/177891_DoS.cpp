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


    int maxStarSum(vector<int>& vals, vector<vector<int>>& edges, int k) {
        vector<vector<int>> adj(size(vals));
        for (const auto& e : edges) {
            if (vals[e[1]] > 0) {
                adj[e[0]].emplace_back(e[1]);
            }
            if (vals[e[0]] > 0) {
                adj[e[1]].emplace_back(e[0]);
            }
        }
        int result = numeric_limits<int>::min();
        for (int u = 0; u < size(vals); ++u) {
            if (1 <= k && k <= size(adj[u])) {
                nth_element(begin(adj[u]), begin(adj[u]) + k - 1, end(adj[u]),
                            [&](const auto& a, const auto& b) {
                                return vals[a] > vals[b];
                            });
            }
            result = max(result, vals[u] + accumulate(cbegin(adj[u]), cbegin(adj[u]) + min(k, static_cast<int>(size(adj[u]))), 0,
                                                      [&](const auto& total, const auto& x) {
                                                          return total + vals[x];
                                                      }));
        }
        return result;
    }


