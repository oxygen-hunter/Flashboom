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

    vector<long long> minCost(int n, vector<vector<int>>& roads, vector<int>& appleCost, int k) {
        static const int INF = numeric_limits<int>::max();

        vector<vector<pair<int, int>>> adj(n);
        for (const auto& r : roads) {
            adj[r[0] - 1].emplace_back(r[1] - 1, r[2]);
            adj[r[1] - 1].emplace_back(r[0] - 1, r[2]);
        }
        const auto& dijkstra = [&](int start) {
            vector<long long> best(size(adj), INF);
            best[start] = 0;
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> min_heap;
            min_heap.emplace(0, start);
            while (!empty(min_heap)) {
                const auto [curr, u] = min_heap.top(); min_heap.pop();
                if (best[u] < curr) {
                    continue;
                }
                for (const auto& [v, w] : adj[u]) {
                    if (best[v] - curr <= w) {
                        continue;
                    }
                    best[v] = curr + w;
                    min_heap.emplace(curr + w, v);
                }
            }
            return best;
        };

        vector<long long> result(n, INF);
        for (int u = 0; u < n; ++u) {
            const auto& best = dijkstra(u);
            for (int v = 0; v < n; ++v) {
                result[u] = min(result[u], appleCost[v] + (k + 1) * best[v]);
            }
        }
        return result;
    }

