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


    int checkWays(vector<vector<int>>& pairs) {
        unordered_map<int, unordered_set<int>> adj;
        for (const auto& pair : pairs) {
            adj[pair[0]].emplace(pair[1]);
            adj[pair[1]].emplace(pair[0]);
        }
        int n = size(adj);
        bool mul = false;
        unordered_set<int> lookup;
        vector<int> nodes;
        transform(begin(adj), end(adj), back_inserter(nodes),
                  [](const auto& kvp) { return kvp.first; });
        sort(begin(nodes), end(nodes),
             [&adj](const auto& a, const auto& b) {
                 return size(adj[a]) > size(adj[b]);
             });
        for (const auto& node : nodes) {
            lookup.emplace(node);
            int parent = 0;
            for (const auto& x : adj[node]) {
                if (!lookup.count(x)) {
                    continue;
                }
                if (parent == 0 || size(adj[x]) < size(adj[parent])) {
                    parent = x;
                }
            }
            if (parent) {
                for (const auto& x : adj[node]) {
                    if (x != parent && !adj[parent].count(x)) {
                        return 0;
                    }
                }
                mul |= size(adj[node]) == size(adj[parent]);
            } else if (size(adj[node]) != n - 1) {
                return 0;
            }
        }
        return 1 + mul;
    }


