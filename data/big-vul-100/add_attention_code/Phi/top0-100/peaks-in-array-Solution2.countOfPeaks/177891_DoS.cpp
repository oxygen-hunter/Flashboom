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

    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
        const auto& check = [&](int i) {
            return nums[i - 1] < nums[i] && nums[i] > nums[i + 1];
        };

        BIT bit(size(nums));
        for (int i = 1; i + 1 < size(nums); ++i) {
            if (check(i)) {
                bit.add(i, +1);
            }
        }

        const auto& update = [&](int x, int d) {
            for (int i = max(x - 1, 1); i <= min(x + 1, static_cast<int>(size(nums)) - 2); ++i) {
                if (check(i)) {
                    bit.add(i, d);
                }
            }
        };

        vector<int> result;
        for (const auto& q : queries) {
            const int t = q[0], x = q[1], y = q[2];
            if (t == 1) {
                result.emplace_back(y - 1 >= x + 1 ? bit.query(y - 1) - bit.query((x + 1) - 1) : 0);
                continue;
            }
            update(x, -1);
            nums[x] = y;
            update(x, +1);
        }
        return result;
    }

