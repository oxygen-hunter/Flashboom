ztype(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    ref tnref;
    int code = array_get(imemory, op, (long)r_btype(op - 1), &tnref);

    if (code < 0)
        return code;
    if (!r_has_type(&tnref, t_name)) {
         /* Must be either a stack underflow or a t_[a]struct. */
         check_op(2);
         {                       /* Get the type name from the structure. */
            if (op[-1].value.pstruct != 0x00) {
             const char *sname =
                 gs_struct_type_name_string(gs_object_type(imemory,
                                                           op[-1].value.pstruct));
            int code = name_ref(imemory, (const byte *)sname, strlen(sname),
                                (ref *) (op - 1), 0);

            if (code < 0)
                return code;
            } else
                return_error(gs_error_stackunderflow);
        }
        r_set_attrs(op - 1, a_executable);
    } else {
        ref_assign(op - 1, &tnref);
    }
    pop(1);
    return 0;
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

