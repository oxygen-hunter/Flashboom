zsetcolor(i_ctx_t * i_ctx_p)
{
    os_ptr                  op = osp;
    es_ptr ep;
    const gs_color_space *  pcs = gs_currentcolorspace(igs);
    gs_client_color         cc;
    int                     n_comps, n_numeric_comps, num_offset = 0, code, depth;
    PS_colour_space_t *space;

    /* initialize the client color pattern pointer for GC */
    cc.pattern = 0;

    /* check for a pattern color space */
    if ((n_comps = cs_num_components(pcs)) < 0) {
        n_comps = -n_comps;
         if (r_has_type(op, t_dictionary)) {
             ref     *pImpl, pPatInst;
 
            code = dict_find_string(op, "Implementation", &pImpl);
            if (code != 0) {
                 code = array_get(imemory, pImpl, 0, &pPatInst);
                 if (code < 0)
                     return code;
                n_numeric_comps = ( pattern_instance_uses_base_space(cc.pattern)
                      ? n_comps - 1
                      : 0 );
            } else
                n_numeric_comps = 0;
        } else
            n_numeric_comps = 0;
        num_offset = 1;
    } else
        n_numeric_comps = n_comps;

    /* gather the numeric operands */
    code = float_params(op - num_offset, n_numeric_comps, cc.paint.values);
    if (code < 0)
        return code;
    /* The values are copied to graphic state and compared with */
    /* other colors by memcmp() in gx_hld_saved_color_equal()   */
    /* This is the easiest way to avoid indeterminism */
    memset(cc.paint.values + n_numeric_comps, 0,
            sizeof(cc.paint.values) - sizeof(*cc.paint.values)*n_numeric_comps);

    code = get_space_object(i_ctx_p, &istate->colorspace[0].array, &space);
    if (code < 0)
        return code;
    if (space->validatecomponents) {
        code = space->validatecomponents(i_ctx_p,
                                         &istate->colorspace[0].array,
                                         cc.paint.values, n_numeric_comps);
        if (code < 0)
            return code;
    }

    /* pass the color to the graphic library */
    if ((code = gs_setcolor(igs, &cc)) >= 0) {

        if (n_comps > n_numeric_comps) {
            istate->pattern[0] = *op;      /* save pattern dict or null */
        }
    }

    /* Check the color spaces, to see if we need to run any tint transform
     * procedures. Some Adobe applications *eg Photoshop) expect that the
     * tint transform will be run and use this to set up duotone DeviceN
     * spaces.
     */
    code = validate_spaces(i_ctx_p, &istate->colorspace[0].array, &depth);
    if (code < 0)
        return code;
    /* Set up for the continuation procedure which will do the work */
    /* Make sure the exec stack has enough space */
    check_estack(5);
    /* A place holder for data potentially used by transform functions */
    ep = esp += 1;
    make_int(ep, 0);
    /* Store the 'depth' of the space returned during checking above */
    ep = esp += 1;
    make_int(ep, 0);
    /* Store the 'stage' of processing (initially 0) */
    ep = esp += 1;
    make_int(ep, 0);
    /* Store a pointer to the color space stored on the operand stack
     * as the stack may grow unpredictably making further access
     * to the space difficult
     */
    ep = esp += 1;
    *ep = istate->colorspace[0].array;
    /* Finally, the actual continuation routine */
    push_op_estack(setcolor_cont);
    return o_push_estack;
}

    int maxHappyGroups(int batchSize, vector<int>& groups) {
        vector<int> count(batchSize);
        for (const auto& i : groups) {
            ++count[i % size(count)];
        }
        int result = count[0];
        count[0] = 0;
        for (int i = 1; i <= size(count) / 2; ++i) {
            int pair_count = 2 * i != size(count) ? min(count[i], count[size(count) - i]) : count[i] / 2;
            result += pair_count;
            count[i] -= pair_count;
            count[size(count) - i] -= pair_count;
        }
        unordered_map<int, int> new_count;
        for (int i = 0; i < size(count); ++i) {
            if (count[i]) {
                new_count[i] = count[i];
            }
        }
        int max_mask = accumulate(cbegin(new_count), cend(new_count), 1,
                                  [](int total, pair<int, int> kvp) {
                                      return total * (kvp.second + 1);
                                  });
        vector<int> dp(max_mask);
        for (int mask = 0; mask < size(dp); ++mask) {
            int remain = 0;
            int curr = mask, basis = 1;
                for (const auto& [i, c] : new_count) {
                // mask: a0 + a1 * (c0 + 1)  + a2 * (c0 + 1) * (c1 + 1) + ... + a(b-1) * (c0 + 1) * (c1 + 1) * ... * (c(b-2) + 1)
                int ai = curr % (count[i] + 1);
                if (ai > 0) {
                    dp[mask] = max(dp[mask], dp[mask - basis]);
                }
                remain = (remain + ai * i) % batchSize;
                basis *= (c + 1), curr /= (c + 1);
            }
            if (mask != size(dp) - 1 && remain == 0) {
                ++dp[mask];
            }
        }
        return result + dp.back();
    }

