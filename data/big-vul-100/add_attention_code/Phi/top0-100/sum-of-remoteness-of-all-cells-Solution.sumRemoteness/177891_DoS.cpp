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

    long long sumRemoteness(vector<vector<int>>& grid) {
        static const vector<pair<int, int>> DIRECTIONS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        const auto& bfs = [&](int i, int j) {
            int64_t total = grid[i][j];
            int cnt = 1;
            grid[i][j] = -1;
            vector<pair<int64_t, int>> q = {{i, j}};
            while (!empty(q)) {
                vector<pair<int64_t, int>> new_q;
                for (const auto& [i, j] : q) {
                    for (const auto& [di, dj] : DIRECTIONS) {
                        int ni = i + di, nj = j + dj;
                        if (!(0 <= ni && ni < size(grid) &&
                              0 <= nj && nj < size(grid[0]) &&
                              grid[ni][nj] != -1)) {
                            continue;
                        }
                        total += grid[ni][nj];
                        ++cnt;
                        grid[ni][nj] = -1;
                        new_q.emplace_back(ni, nj);
                    }
                }
                q = move(new_q);
            }
            return pair(total, cnt);
        };
    
        vector<pair<int64_t, int>> groups;
        for (int i = 0; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]); ++j) {
                if (grid[i][j] == -1) {
                    continue;
                }
                groups.emplace_back(bfs(i, j));
            }
        }
        int64_t total = 0;
        for (const auto& [t, _] : groups) {
            total += t;
        }
        int64_t result = 0;
        for (const auto& [t, c] : groups) {
            result += (total - t) * c;
        }
        return result;
    }

