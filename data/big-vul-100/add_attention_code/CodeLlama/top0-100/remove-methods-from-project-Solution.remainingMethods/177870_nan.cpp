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


    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> adj(n);
        const auto& bfs = [&]() {
            vector<bool> lookup(n);
            lookup[k] = true;
            vector<int> q = {k};
            while (!empty(q)) {
                vector<int> new_q;
                for (const auto& u : q) {
                    for (const auto& v : adj[u]) {
                        if (lookup[v]) {
                            continue;
                        }
                        lookup[v] = true;
                        new_q.emplace_back(v);
                    }
                }
                q = move(new_q);
            }
            return lookup;
        };
       
        for (const auto& e : invocations) {
            adj[e[0]].emplace_back(e[1]);
        }
        const auto& lookup = bfs();
        for (const auto& e : invocations) {
            if (lookup[e[0]] != lookup[e[1]]) {
                vector<int> result(n);
                iota(begin(result), end(result), 0);
                return result;
            }
        }
        vector<int> result;
        for (int u = 0; u < n; ++u) {
            if (!lookup[u]) {
                result.emplace_back(u);
            }
        }
        return result;
    }


