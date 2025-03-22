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


    string shortestCommonSupersequence(string str1, string str2) {
        vector<vector<int>> dp(2, vector<int>(str2.size() + 1));
        vector<vector<tuple<int, int, char>>> bt(str1.size() + 1,
                                                 vector<tuple<int, int, char>>(str2.size() + 1));
        for (int i = 0; i < str1.length(); ++i) {
            bt[i + 1][0] = {i, 0, str1[i]};
        }
        for (int j = 0; j < str2.length(); ++j) {
            bt[0][j + 1] = {0, j, str2[j]};
        }
        for (int i = 0; i < str1.length(); ++i) {
            for (int j = 0; j < str2.length(); ++j) {
                if (dp[i % 2][j + 1] > dp[(i + 1) % 2][j]) {
                    dp[(i + 1) % 2][j + 1] = dp[i % 2][j + 1];
                    bt[i + 1][j + 1] = {i, j + 1, str1[i]};
                } else {
                    dp[(i + 1) % 2][j + 1] = dp[(i + 1) % 2][j];
                    bt[i + 1][j + 1] = {i + 1, j, str2[j]};
                }
                if (str1[i] != str2[j]) {
                    continue;
                }
                if (dp[i % 2][j] + 1 > dp[(i + 1) % 2][j + 1]) {
                    dp[(i + 1) % 2][j + 1] = dp[i % 2][j] + 1;
                    bt[i + 1][j + 1] = {i, j, str1[i]};
                }
            }
        }
        
        int i = str1.length(), j = str2.length();
        char c = 0;
        string result;
        while (i != 0 || j != 0) {
            tie(i, j, c) = bt[i][j];
            result.push_back(c);
        }
        reverse(result.begin(), result.end());
        return result;
    }


