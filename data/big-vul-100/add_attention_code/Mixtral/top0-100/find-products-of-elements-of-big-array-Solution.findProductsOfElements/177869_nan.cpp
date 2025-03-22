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

    vector<int> findProductsOfElements(vector<vector<long long>>& queries) {
        const auto& binary_search = [](auto left, auto right, const auto& check) {
            while (left <= right) {
                const auto mid = left + ((right - left) / 2);
                if (check(mid)) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return left;
        };

        const auto& powmod = [&](auto a, auto b, int mod) {
            a %= mod;
            auto result = 1 % mod;
            while (b) {
                if (b & 1) {
                    result = result * a % mod;
                }
                a = a * a % mod;
                b >>= 1;
            }
            return result;
        };

        const auto& count1 = [&](auto x) {
            auto result = 0ll;
            for (int i = 0; (1ll << i) <= x; ++i) {
                const auto mask = (1ll << (i + 1)) - 1;
                result += ((x & ~mask) >> 1) + max((x & mask) - (1ll << i) + 1, 0ll);
            }
            return result;
        };
        
        const auto& count2 = [&](auto x) {
            auto result = 0ll;
            for (int i = 0; (1ll << i) <= x; ++i) {
                const auto mask = (1ll << (i + 1)) - 1;
                result += (((x & ~mask) >> 1) + max((x & mask) - (1ll << i) + 1, 0ll)) * i;
            }
            return result;
        };
    
        const auto& f = [&](auto x) {
            const auto y = binary_search(1ll, x - 1, [&](auto i) {
                return count1(i) >= x;
            });
            auto result = count2(y - 1);
            x -= count1(y - 1);
            for (int i = 0; (1ll << i) <= y; ++i) {
                if ((y & (1ll << i)) == 0) {
                    continue;
                }
                result += i;
                if (--x == 0) {
                    break;
                }
            }
            return result;
        };
    
        vector<int> result(size(queries));
        for (int i = 0; i < size(queries); ++i) {
            const auto left = queries[i][0], right = queries[i][1], mod = queries[i][2];
            result[i] =  powmod(2ll, f(right + 1) - f(left), mod);
        }
        return result;
    }

