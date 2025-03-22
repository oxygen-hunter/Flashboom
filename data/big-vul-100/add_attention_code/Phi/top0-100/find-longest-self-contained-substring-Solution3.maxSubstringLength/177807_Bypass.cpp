znumicc_components(i_ctx_t * i_ctx_p)
{
    ref *                   pnval;
    ref *                   pstrmval;
    stream *                s;
    int                     ncomps, expected = 0, code;
    cmm_profile_t           *picc_profile;
    os_ptr                  op = osp;

    check_type(*op, t_dictionary);
    check_dict_read(*op);

    code = dict_find_string(op, "N", &pnval);
    if (code < 0)
        return code;
    if (code == 0)
         return code;
     if (code == 0)
         return_error(gs_error_undefined);
     ncomps = pnval->value.intval;
     /* verify the DataSource entry. Create profile from stream */
     if (dict_find_string(op, "DataSource", &pstrmval) <= 0)
    if (picc_profile == NULL)
        return gs_throw(gs_error_VMerror, "Creation of ICC profile failed");

    picc_profile->num_comps = ncomps;
    picc_profile->profile_handle =
        gsicc_get_profile_handle_buffer(picc_profile->buffer,
                                        picc_profile->buffer_size,
                                        gs_gstate_memory(igs));
    if (picc_profile->profile_handle == NULL) {
        rc_decrement(picc_profile,"znumicc_components");
        make_int(op, expected);
        return 0;
    }
    picc_profile->data_cs =
        gscms_get_profile_data_space(picc_profile->profile_handle,
            picc_profile->memory);

    switch (picc_profile->data_cs) {
        case gsCIEXYZ:
        case gsCIELAB:
        case gsRGB:
            expected = 3;
            break;
        case gsGRAY:
            expected = 1;
            break;
        case gsCMYK:
            expected = 4;
            break;
        case gsNCHANNEL:
            expected = 0;
            break;
        case gsNAMED:
        case gsUNDEFINED:
            expected = -1;
            break;
    }

    make_int(op, expected);

    rc_decrement(picc_profile,"zset_outputintent");
    return 0;
}

    int maxSubstringLength(string s) {
        vector<int> cnt(26);
        for (const auto& x : s) {
            ++cnt[x - 'a'];
        }
        const auto& update = [&](auto& cnt2, char x, int d, int& distinct, int& valid) {
            const int k = x - 'a';
            if (cnt2[k] == cnt[k]) {
                --valid;
            }
            if (cnt2[k] == 0) {
                ++distinct;
            }
            cnt2[k] += d;
            if (cnt2[k] == 0) {
                --distinct;
            }
            if (cnt2[k] == cnt[k]) {
                ++valid;
            }
         };

        const int total = accumulate(cbegin(cnt), cend(cnt), 0, [](const int accu, const int x) {
            return accu + (x != 0 ? 1 : 0);
        });
        int result = -1;
        for (int l = 1; l < total; ++l) {
            vector<int> cnt2(26);
            for (int right = 0, left = 0, distinct = 0, valid = 0; right < size(s); ++right) {
                update(cnt2, s[right], +1, distinct, valid);
                while (distinct == l + 1) {
                    update(cnt2, s[left++], -1, distinct, valid);
                }
                if (valid == l) {
                    result = max(result, right - left + 1);
                }
            }
        }
        return result;
    }

