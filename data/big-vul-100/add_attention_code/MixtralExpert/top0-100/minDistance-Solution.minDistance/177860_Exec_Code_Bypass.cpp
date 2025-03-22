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


        int minDistance(string word1, string word2) {
            const size_t m = word1.size();
            const size_t n = word2.size();

            if(m < n)
                return minDistance(word2, word1);

            vector<size_t> f(n + 1, 0);
            size_t upper_left;

            for(size_t i = 0; i < n + 1; ++i)
                f[i] = i;

            for(size_t i = 1; i < m + 1; ++i) {
                upper_left = f[0];
                f[0] = i;
                for(size_t j = 1; j < n + 1; ++j) {
                    size_t upper = f[j];
                    if(word1[i - 1] == word2[j - 1])
                        f[j] = upper_left;
                    else {
                        f[j] = 1 + min(upper_left, min(f[j - 1], f[j]));
                    }
                    upper_left = upper;
                }
            }

            return f[n];
        }


