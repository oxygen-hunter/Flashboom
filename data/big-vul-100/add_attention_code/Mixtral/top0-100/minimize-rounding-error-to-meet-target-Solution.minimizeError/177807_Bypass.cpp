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

    string minimizeError(vector<string>& prices, int target) {
        vector<double> errors;
        int lower = 0, upper = 0;
        for (const auto& price : prices) {
            const auto& p = stod(price);
            lower += floor(p);
            upper += ceil(p);
            if (p != floor(p)) {
                errors.emplace_back(p - floor(p));
            }
        }
        if (target < lower || target > upper) {
            return "-1";
        }

        int lower_round_count = upper - target;
        nth_element(errors.begin(), errors.begin() + lower_round_count, errors.end());
        double min_error = 0.0;
        for (int i = 0; i < errors.size(); ++i) {
            if (i < lower_round_count) {
                min_error += errors[i];
            } else {
                min_error += 1.0 - errors[i];
            }
        }
        const auto& result = to_string(min_error);
        return result.substr(0, result.find(".") + 4);
    }

