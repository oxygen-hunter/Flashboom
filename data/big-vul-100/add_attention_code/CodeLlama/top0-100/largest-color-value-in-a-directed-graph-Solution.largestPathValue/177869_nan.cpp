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


    int largestPathValue(string colors, vector<vector<int>>& edges) {
        vector<vector<int>> adj(size(colors));
        vector<int> in_degree(size(colors));
        for (const auto& edge : edges) {
            adj[edge[0]].emplace_back(edge[1]);
            ++in_degree[edge[1]];
        }
        vector<int> q;
        for (int i = 0; i < size(colors); ++i) {
            if (!in_degree[i]) {
                q.emplace_back(i);
            }
        }
        vector<vector<int>> dp(size(colors), vector<int>(26));
        int result = -1, cnt = 0;
        while (!empty(q)) {
            vector<int> new_q;
            for (const auto& u : q) {
                ++cnt;
                result = max(result, ++dp[u][colors[u] - 'a']);
                for (const auto& v : adj[u]) {
                    for (int c = 0; c < 26; ++c) {
                        dp[v][c] = max(dp[v][c], dp[u][c]);
                    }
                    if (!--in_degree[v]) {
                        new_q.emplace_back(v);
                    }
                }
            }
            q = move(new_q);
        }
        return cnt == size(colors) ? result : -1;
    }


