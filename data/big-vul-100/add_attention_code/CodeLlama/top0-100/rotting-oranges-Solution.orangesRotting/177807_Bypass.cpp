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


    int orangesRotting(vector<vector<int>>& grid) {
        static const vector<pair<int, int>> directions{{0, 1}, {1, 0},
                                                       {0, -1}, {-1, 0}};

        int count = 0;
        queue<tuple<int, int, int>> q;
        for (int r = 0; r < grid.size(); ++r) {
            for (int c = 0; c < grid[r].size(); ++c) {
                if (grid[r][c] == 2) {
                    q.emplace(r, c, 0);
                } else if (grid[r][c]  == 1) {
                    ++count;
                }
            }
        }

        int result = 0;
        while (!q.empty()) {
            int r, c;
            tie(r, c, result) = q.front(); q.pop();
            for (const auto& d : directions) {
                int nr = r + d.first, nc = c + d.second;
                if  (!(0 <= nr && nr < grid.size() &&
                       0 <= nc && nc < grid[r].size())) {
                    continue;
                }
                if (grid[nr][nc] == 1) {
                    --count;
                    grid[nr][nc] = 2;
                    q.emplace(nr, nc, result + 1);
                }
            }
        }
        return (count == 0) ? result : -1;
    }


