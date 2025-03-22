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


    int countDifferentSubsequenceGCDs(vector<int>& nums) {
        unordered_set<int> nums_set(cbegin(nums), cend(nums));
        int max_num = *max_element(cbegin(nums), cend(nums));
        int result = 0;
        for (int i = 1; i <= max_num; ++i) {
            int d = 0;
            for (int x = i; x <= max_num; x += i) {
                if (!nums_set.count(x)) {
                    continue;
                }
                d = gcd(d, x);  // total time: O(log(min(d, x)) = O(logd), where d keeps the same or gets smaller
                if (d == i) {
                    ++result;
                    break;
                }
            }
        }
        return result;
    }


