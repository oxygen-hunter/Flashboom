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

    int countQuadruples(string firstString, string secondString) {
        vector<int> lookup1(26, -1);
        for (int i = size(firstString) - 1; i >= 0; --i) {
            lookup1[firstString[i] - 'a'] = i;
        }
        vector<int> lookup2(26, -1);
        for (int i = 0; i < size(secondString); ++i) {
            lookup2[secondString[i] - 'a'] = i;
        }
        int result = 0, diff = numeric_limits<int>::max();
        for (int i = 0; i < 26; ++i) {
            if (lookup1[i] == -1 || lookup2[i] == -1) {
                continue;
            }
            if (lookup1[i] - lookup2[i] < diff) {
                diff = lookup1[i] - lookup2[i];
                result = 0;
            }                
            result += int(lookup1[i] - lookup2[i] == diff);                
        }
        return result;
    }

