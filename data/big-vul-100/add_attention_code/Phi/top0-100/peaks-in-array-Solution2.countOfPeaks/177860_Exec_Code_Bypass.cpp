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

    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
        const auto& check = [&](int i) {
            return nums[i - 1] < nums[i] && nums[i] > nums[i + 1];
        };

        BIT bit(size(nums));
        for (int i = 1; i + 1 < size(nums); ++i) {
            if (check(i)) {
                bit.add(i, +1);
            }
        }

        const auto& update = [&](int x, int d) {
            for (int i = max(x - 1, 1); i <= min(x + 1, static_cast<int>(size(nums)) - 2); ++i) {
                if (check(i)) {
                    bit.add(i, d);
                }
            }
        };

        vector<int> result;
        for (const auto& q : queries) {
            const int t = q[0], x = q[1], y = q[2];
            if (t == 1) {
                result.emplace_back(y - 1 >= x + 1 ? bit.query(y - 1) - bit.query((x + 1) - 1) : 0);
                continue;
            }
            update(x, -1);
            nums[x] = y;
            update(x, +1);
        }
        return result;
    }

