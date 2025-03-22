zrestore(i_ctx_t *i_ctx_p)
 {
     os_ptr op = osp;
    alloc_save_t *asave;
    bool last;
    vm_save_t *vmsave;
    int code = restore_check_operand(op, &asave, idmemory);
 
     if (code < 0)
         return code;
     if_debug2m('u', imemory, "[u]vmrestore 0x%lx, id = %lu\n",
               (ulong) alloc_save_client_data(asave),
                (ulong) op->value.saveid);
     if (I_VALIDATE_BEFORE_RESTORE)
         ivalidate_clean_spaces(i_ctx_p);
        ivalidate_clean_spaces(i_ctx_p);
    /* Check the contents of the stacks. */
     {
         int code;
 
        if ((code = restore_check_stack(i_ctx_p, &o_stack, asave, false)) < 0 ||
            (code = restore_check_stack(i_ctx_p, &e_stack, asave, true)) < 0 ||
            (code = restore_check_stack(i_ctx_p, &d_stack, asave, false)) < 0
             ) {
             osp++;
             return code;
         }
     }
     /* Reset l_new in all stack entries if the new save level is zero. */
     /* Also do some special fixing on the e-stack. */
     restore_fix_stack(i_ctx_p, &o_stack, asave, false);
    }


    int findShortestCycle(int n, vector<vector<int>>& edges) {
        static const int INF = numeric_limits<int>::max();

        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].emplace_back(e[1]);
            adj[e[1]].emplace_back(e[0]);
        }
        const auto& bfs = [&](int u) {
            int result = INF;
            vector<int> dist(n, INF);
            dist[u] = 0;
            vector<int> q = {u};
            while (!empty(q)) {
                vector<int> new_q;
                for (const auto& u : q) {
                    for (const auto& v : adj[u]) {
                        if (dist[v] != INF) {
                            assert(abs(dist[v] - dist[u]) <= 1);
                            if (dist[v] != dist[u] - 1) {
                                result = min(result, 1 + dist[u] + dist[v]);  // d = dist[u]+1 >= 2, check if any cycle of length 2*d-1 or 2*d exists
                            }
                            continue;
                        }
                        dist[v] = dist[u] + 1;
                        new_q.emplace_back(v);
                    }
                }
                if (result != INF) {  // a cycle of length 2*d-1 or 2*d was found, early return
                    break;
                }
                q = move(new_q);
            }
            return result;
        };

        int result = INF;
        for (int u = 0; u < n; ++u) {
            result = min(result, bfs(u));
        }
        return result != INF ? result : -1;
    }


