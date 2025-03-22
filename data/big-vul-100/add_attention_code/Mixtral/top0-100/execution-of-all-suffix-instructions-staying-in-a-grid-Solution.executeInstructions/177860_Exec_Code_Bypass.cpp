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

    vector<int> executeInstructions(int n, vector<int>& startPos, string s) {
        static const unordered_map<char, pair<int, int>> directions = {
            {'U', {-1, 0}}, {'R', {0, 1}}, {'D', {1, 0}}, {'L', {0, -1}}
        };

        int x0 = startPos[0], y0 = startPos[1];
        int x = 0, y = 0;
        vector<int> result(size(s));
        iota(rbegin(result), rend(result), 1);
        unordered_map<int, vector<int>> lookup_x, lookup_y;
        lookup_x[x0 - x].emplace_back(0);
        lookup_y[y0 - y].emplace_back(0);
        for (int i = 0; i < size(s); ++i) {
            const auto& [dx, dy] = directions.at(s[i]);
            x += dx, y += dy;
            for (const auto& k : {n - x, -x - 1}) {
                if (!lookup_x.count(k)) {
                    continue;
                }
                for (const auto& j : lookup_x[k]) {
                    result[j] = min(result[j], i - j);
                }
                lookup_x.erase(k);
            }
            for (const auto& k : {n - y, -y - 1}) {
                if (!lookup_y.count(k)) {
                    continue;
                }
                for (const auto& j : lookup_y[k]) {
                    result[j] = min(result[j], i - j);
                }
                lookup_y.erase(k);
            }
            lookup_x[x0 - x].emplace_back(i + 1);
            lookup_y[y0 - y].emplace_back(i + 1);
        }
        return result;
    }

