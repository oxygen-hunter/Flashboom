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

    bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) {
        vector<vector<int>> prefix(size(grid) + 1, vector<int>(size(grid[0]) + 1));
        vector<vector<int>> fit(size(grid), vector<int>(size(grid[0])));
        for (int i = 0; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]); ++j) {
                prefix[i + 1][j + 1] = prefix[i + 1][j] + prefix[i][j + 1] - prefix[i][j] + (1 ^ grid[i][j]);
                if (i + 1 >= stampHeight && j + 1 >= stampWidth) {
                    const int x = i + 1 - stampHeight, y = j + 1 - stampWidth;
                    fit[i][j] = static_cast<int>(prefix[i + 1][j + 1] - prefix[x][j + 1] - prefix[i + 1][y] + prefix[x][y] == stampWidth * stampHeight);
                }
            }
        }
        vector<vector<int>> prefix2(size(grid) + 1, vector<int>(size(grid[0]) + 1));
        for (int i = 0; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]); ++j) {
                prefix2[i + 1][j + 1] = prefix2[i + 1][j] + prefix2[i][j + 1] - prefix2[i][j] + fit[i][j];
            }
        }
        for (int i = 0; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]); ++j) {
                const int x = min(i + stampHeight, static_cast<int>(size(grid))), y = min(j + stampWidth, static_cast<int>(size(grid[0])));
                if (!grid[i][j] && !(prefix2[x][y] - prefix2[i][y] - prefix2[x][j] + prefix2[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }

