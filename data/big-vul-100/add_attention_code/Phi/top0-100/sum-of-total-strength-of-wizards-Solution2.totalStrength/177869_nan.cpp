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

    int totalStrength(vector<int>& strength) {
        static const int MOD = 1e9 + 7;
        const auto& add = [&](const int64_t a, const int64_t b) {
            return (a + b) % MOD;
        };
        const auto& sub = [&](const int64_t a, const int64_t b) {
            return (a - b + MOD) % MOD;
        };
        const auto& mult = [&](const int64_t a, const int64_t b) {
            return (a * b) % MOD;
        };
        vector<int64_t> prefix(size(strength) + 1), prefix2(size(strength) + 1);
        for (int i = 0; i < size(strength); ++i) {
            prefix[i + 1] = add(prefix[i], strength[i]);
            prefix2[i + 1] = add(prefix2[i], strength[i] * static_cast<int64_t>(i + 1));
        }
        vector<int64_t> suffix(size(strength) + 1), suffix2(size(strength) + 1);
        for (int i = size(strength) - 1; i >= 0; --i) {
            suffix[i] = add(suffix[i + 1], strength[i]);
            suffix2[i] = add(suffix2[i + 1], strength[i] * (size(strength) - i));
        }
        vector<int> stk = {-1};
        int result = 0;
        for (int i = 0; i <= size(strength); ++i) {
            while (stk.back() != -1 && (i == size(strength) || strength[stk.back()] >= strength[i])) {
                const int x = stk[size(stk) - 2] + 1;
                const int y = stk.back(); stk.pop_back();
                const int z = i - 1;
                // assert(all(strength[j] >= strength[y] for j in xrange(x, y+1)))
                // assert(all(strength[j] > strength[y] for j in xrange(y+1, z+1)))
                const int64_t left = mult(z - y + 1, sub(sub(prefix2[y + 1], prefix2[x]), mult(x, sub(prefix[y + 1], prefix[x]))));
                const int64_t right = mult(y - x + 1, sub(sub(suffix2[y + 1], suffix2[z + 1]), mult(size(strength) - (z + 1), sub(suffix[y + 1], suffix[z + 1]))));
                result = add(result, mult(strength[y], add(left, right)));
            }
            stk.emplace_back(i);
        }
        return result;
    }

