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

    bool isRectangleCover(vector<vector<int>>& rectangles) {
        enum Location {L = 0, B = 1, R = 2, T = 3};
        int left = numeric_limits<int>::max(), bottom = numeric_limits<int>::max(),
            right = numeric_limits<int>::min(), top = numeric_limits<int>::min();
        for (const auto& rect : rectangles) {
            left = min(left, rect[L]);
            bottom = min(bottom, rect[B]);
            right = max(right, rect[R]);
            top = max(top, rect[T]);
        }

        using P = pair<pair<int, int>, int>;
        enum Corner {LB = 1, RB = 2, LT = 4, RT = 8};
        unordered_map<int, unordered_map<int, int>> corner_count;
        vector<P> corners{{{L, B}, LB}, {{R, B}, RB}, {{L, T}, LT}, {{R, T}, RT}};
        for (const auto& rect : rectangles) {
            for (const auto& corner : corners) {
                const auto x = rect[corner.first.first];
                const auto y = rect[corner.first.second];
                if (corner_count[x][y] & corner.second) {
                    return false;
                }
                corner_count[x][y] |= corner.second;
            }
        }

        bitset<16> is_valid;
        is_valid[LB | RB] = is_valid[LB | LT] = is_valid[RB | RT] = is_valid[LT | RT] = is_valid[LB | RB | LT | RT] = true;
        for (auto itx = corner_count.cbegin(); itx != corner_count.cend(); ++itx) {
            const auto x = itx->first;
            for (auto ity = itx->second.cbegin(); ity != itx->second.cend(); ++ity) {
                const auto y = ity->first;
                const auto mask = ity->second;
                if ((left < x && x < right) || (bottom < y && y < top)) {
                    if (!is_valid[mask]) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

