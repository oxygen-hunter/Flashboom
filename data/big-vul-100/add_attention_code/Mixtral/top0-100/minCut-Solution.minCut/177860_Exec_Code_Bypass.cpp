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

        int minCut(string s) {
            const int n = s.size();
            vector<vector<bool> > p(n, vector<bool>(n, false)); // p[i][j]: range [i, j] is a palindrome paritioning of s
            vector<int> f(n + 1, 0); // f[i]: minimum cuts in range [i, n - 1]

            for(int i = 0; i <= n; ++i) {
                f[i] = n - 1 - i;    // initialize f[i] to the max cuts
            }

            for (int i = n - 1; i >= 0; --i) {
                for (int j = i; j < n; ++j) {
                    // [i, j] is palindrome if only if s[i] equals to s[j] and [i + 1, j - 1] is palindrome too
                    if(s[i] == s[j] && ((j - i < 2) || p[i + 1][j - 1])) {
                        p[i][j] = true;
                        f[i] = min(f[i], f[j + 1] + 1);  // f[i] = min(f[j + 1] + 1) for each i <= j <= n - 1
                    }
                }   
            }

            return f[0];
        }

