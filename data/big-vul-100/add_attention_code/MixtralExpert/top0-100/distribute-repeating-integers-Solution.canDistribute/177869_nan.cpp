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


    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        unordered_map<int, int> count;
        for(int i = 0; i < size(nums); ++i) {
            ++count[nums[i]];
        }
        int total = (1 << size(quantity)) - 1;
        vector<int> requirement(total + 1);
        for (int mask = 0; mask < size(requirement); ++mask) {  // Time: O(2^m)
            for (int i = 0; i < size(quantity); ++i) {  // Time: O(m)
                if (mask & (1 << i)) {
                    requirement[mask] += quantity[i];
                }
            }
        }
        vector<vector<int>> dp(2, vector<int>(total + 1));
        dp[0][0] = 1;
        int i = 0;
        vector<int> cnts;
        for (const auto& [_, cnt] : count) {
            cnts.emplace_back(cnt);
        }
        if (size(quantity) < size(cnts)) {  // at most use top m cnts
            nth_element(begin(cnts), begin(cnts) + size(quantity) - 1, end(cnts), greater<int>());
            cnts.resize(size(quantity));
        }
        for (int i = 0; i < size(cnts); ++i) {  // Time: O(m)
            dp[(i + 1) % 2] = vector<int>(total + 1);
            // submask enumeration:
            // => sum(nCr(m, k) * 2^k for k in xrange(m+1)) = (1 + 2)^m = 3^m
            // => Time: O(3^m), see https://cp-algorithms.com/algebra/all-submasks.html
            for (int mask = total; mask >= 0; --mask) {
                dp[(i + 1) % 2][mask] |= dp[i % 2][mask];
                for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
                    if (requirement[submask] <= cnts[i] && dp[i % 2][mask ^ submask]) {
                        dp[(i + 1) % 2][mask] = 1;
                    }
                }
            }
        }
        return dp[size(cnts) % 2][total];
    }


