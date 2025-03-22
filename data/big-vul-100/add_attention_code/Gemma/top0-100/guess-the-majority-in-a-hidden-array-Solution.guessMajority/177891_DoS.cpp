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


    int guessMajority(ArrayReader &reader) {
        int count_a = 1, count_b = 0, idx_b = -1;
        const auto& value_0_1_2_3 = reader.query(0, 1, 2, 3);
        int value_0_1_2_i = -1;
        for (int i = reader.length() - 1; i >= 4; --i) {
            value_0_1_2_i = reader.query(0, 1, 2, i);
            if (value_0_1_2_i == value_0_1_2_3) {  // nums[i] == nums[3]
                ++count_a;
            } else {
                ++count_b;
                idx_b = i;
            }
        }
        const auto& value_0_1_2_4 = value_0_1_2_i;
        for (int i = 0; i < 3; ++i) {
            vector<int> a_b;
            for (int j = 0; j < 3; ++j) {
                if (j == i) {
                    continue;
                }
                a_b.emplace_back(j);
            }
            const auto& value_a_b_3_4 = reader.query(a_b[0], a_b[1], 3, 4);
            if (value_a_b_3_4 == value_0_1_2_4) {  // nums[i] == nums[3]
                ++count_a;
            } else {
                ++count_b;
                idx_b = i;
            }
        }
        if (count_a == count_b) {
            return -1;
        }
        return count_a > count_b ? 3 : idx_b;
    }


