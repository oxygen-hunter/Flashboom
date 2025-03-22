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


    int maxTrailingZeros(vector<vector<int>>& grid) {
        const auto& factor = [](int x) {
            static const array<int, 2> primes = {2, 5};
            array<int, 2> cnt = {0, 0};
            for (int i = 0; i < size(primes); ++i) {
                while (x && x % primes[i] == 0) {
                    x /= primes[i];
                    ++cnt[i];
                }
            }
            return cnt;
        };
        const auto& add = [](const auto& a, const auto& b) {
            return array<int, 2>{a[0] + b[0], a[1] + b[1]};
        };
        const auto& sub = [](const auto& a, const auto& b) {
            return array<int, 2>{a[0] - b[0], a[1] - b[1]};
        };
        const auto& count = [](const auto& a) {
            return min(a[0], a[1]);
        };

        vector<vector<array<int, 2>>> left(size(grid), vector<array<int, 2>>(size(grid[0])));
        for (int i = 0; i < size(grid); ++i) {
            left[i][0] = factor(grid[i][0]);
            for (int j = 1; j < size(grid[0]); ++j) {
                left[i][j] = add(left[i][j - 1], factor(grid[i][j]));
            }
        }
        int result = 0;
        for (int j = 0; j < size(grid[0]); ++j) {
            array<int, 2> total = {0, 0};
            for (int i = 0; i < size(grid); ++i) {
                total = add(total, factor(grid[i][j]));
            }
            array<int, 2> up = {0, 0};
            for (int i = 0; i < size(grid); ++i) {
                const auto& right = j ? sub(left[i].back(), left[i][j - 1]) : left[i].back();
                result = max({result, count(add(left[i][j], up)), count(add(right, up))});
                up = add(up, factor(grid[i][j]));
                const auto& down = sub(total, up);
                result = max({result, count(add(left[i][j], down)), count(add(right, down))});
            }
        }
        return result;
    }


