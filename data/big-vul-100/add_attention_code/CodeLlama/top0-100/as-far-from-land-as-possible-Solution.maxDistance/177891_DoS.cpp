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


    int maxDistance(vector<vector<int>>& grid) {
        static const vector<pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        queue<pair<int, int>> q;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j]) {
                    q.emplace(i, j);
                }
            }
        }
        if (q.size() == grid.size() * grid[0].size()) {
            return -1;
        }
        int level = -1;
        while (!q.empty()) {
            queue<pair<int, int>> next_q;
            while (!q.empty()) {
                const auto [x, y] = q.front(); q.pop();
                for (const auto& [dx, dy] : directions) {
                    const auto& nx = x + dx;
                    const auto& ny = y + dy;
                    if (!(0 <= nx && nx < grid.size() && 
                          0 <= ny && ny < grid[0].size() && 
                          grid[nx][ny] == 0)) {
                        continue;
                    }
                    next_q.emplace(nx, ny);
                    grid[nx][ny] = 1;
                }
            }
            q = move(next_q);
            ++level;
        }
        return level;
    }


