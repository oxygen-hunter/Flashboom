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


    int minimumCost(int n, vector<vector<int>>& highways, int discounts) {
        using P = pair<int, int>;
        unordered_map<int, vector<P>> adj;
        for (const auto& highway : highways) {
            int u, v, w;
            tie(u, v, w) = make_tuple(highway[0], highway[1], highway[2]);
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        
        unordered_map<int, unordered_map<int, int>> best;
        best[0][discounts] = 0;
        using T = tuple<int, int, int>;
        priority_queue<T, vector<T>, greater<T>> min_heap;
        min_heap.emplace(0, 0, discounts);
        while (!empty(min_heap)) {
            auto [total, u, k] = min_heap.top(); min_heap.pop();
            if ((best.count(u) && best[u].count(k) &&  best[u][k] < total)) {
                continue;
            }
            if (u == n - 1) {
                return total;
            }
            for (const auto& [v, w] : adj[u]) {
                if (!best.count(v) ||
                    !best[v].count(k) ||
                    total + w < best[v][k]) {
                    best[v][k] = total + w;
                    min_heap.emplace(total + w, v, k);
                }
                if (k > 0 &&
                    (!best.count(v) ||
                    !best[v].count(k - 1) ||
                    total + w / 2 < best[v][k - 1])) {
                    best[v][k - 1] = total + w / 2;
                    min_heap.emplace(total + w / 2, v, k - 1);
                }
            }
        }
        return -1;
    }


