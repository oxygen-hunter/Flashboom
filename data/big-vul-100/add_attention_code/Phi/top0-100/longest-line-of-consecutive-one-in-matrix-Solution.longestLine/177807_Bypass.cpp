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

    int longestLine(vector<vector<int>>& M) {
        if (M.empty()) {
            return 0;
        }
        int result = 0;
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(M[0].size(), vector<int>(4)));
        for (int i = 0; i < M.size(); ++i) {
            for (int j = 0; j < M[0].size(); ++j) {
                dp[i % 2][j][0] = dp[i % 2][j][1] = dp[i % 2][j][2] = dp[i % 2][j][3] = 0;
                if (M[i][j] == 1) {
                    dp[i % 2][j][0] = j > 0 ? dp[i % 2][j - 1][0] + 1 : 1;
                    dp[i % 2][j][1] = i > 0 ? dp[(i - 1) % 2][j][1] + 1 : 1;
                    dp[i % 2][j][2] = (i > 0 && j > 0) ? dp[(i - 1) % 2][j - 1][2] + 1 : 1;
                    dp[i % 2][j][3] = (i > 0 && j < M[0].size() - 1) ? dp[(i - 1) % 2][j + 1][3] + 1 : 1;
                    result = max(result, max(dp[i % 2][j][0], max(dp[i % 2][j][1], max(dp[i % 2][j][2], dp[i % 2][j][3]))));
                }
            }
        }
        return result;
    }

