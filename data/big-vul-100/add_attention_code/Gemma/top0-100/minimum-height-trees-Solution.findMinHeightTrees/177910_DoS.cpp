token_continue(i_ctx_t *i_ctx_p, scanner_state * pstate, bool save)
{
    os_ptr op = osp;
     int code;
     ref token;
 
     /* Note that gs_scan_token may change osp! */
     pop(1);                     /* remove the file or scanner state */
 again:
            gs_scanner_error_object(i_ctx_p, pstate, &i_ctx_p->error_object);
            break;
        case scan_BOS:
            code = 0;
        case 0:         /* read a token */
            push(2);
            ref_assign(op - 1, &token);
            make_true(op);
            break;
        case scan_EOF:          /* no tokens */
            push(1);
            make_false(op);
            code = 0;
            break;
        case scan_Refill:       /* need more data */
            code = gs_scan_handle_refill(i_ctx_p, pstate, save,
                                      ztoken_continue);
            switch (code) {
                case 0: /* state is not copied to the heap */
                    goto again;
                case o_push_estack:
                    return code;
            }
            break;              /* error */
    }


    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        if (n == 1) {
            return {0};
        }

        unordered_map<int, unordered_set<int>> neighbors;
        for (const auto& e : edges) {
            int u, v;
            tie(u, v) = e;
            neighbors[u].emplace(v);
            neighbors[v].emplace(u);
        }

        vector<int> pre_level, cur_level;
        unordered_set<int> unvisited;
        for (int i = 0; i < n; ++i) {
            if (neighbors[i].size() == 1) {  // A leaf.
                pre_level.emplace_back(i);
            }
            unvisited.emplace(i);
        }

        // A graph can have 2 MHTs at most.
        // BFS from the leaves until the number 
        // of the unvisited nodes is less than 3.
        while (unvisited.size() > 2) {
            cur_level.clear();
            for (const auto& u : pre_level) {
                unvisited.erase(u);
                for (const auto& v : neighbors[u]) {
                    if (unvisited.count(v)) { 
                        neighbors[v].erase(u);
                        if (neighbors[v].size() == 1) {
                            cur_level.emplace_back(v);
                        }
                    }
                }
            }
            swap(pre_level, cur_level);
        }

        vector<int> res(unvisited.begin(), unvisited.end());
        return res;
    }


