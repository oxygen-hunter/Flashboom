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


    int minimumSubarrayLength(vector<int>& nums, int k) {
        const auto& bit_length = [](int x) {
            return (x ? std::__lg(x) : -1) + 1;
        };
    
        const int total = accumulate(cbegin(nums), cend(nums), 0, [](const auto& x, const auto& y) {
            return x | y;
        });
        if (total < k) {
            return -1;
        }
        vector<int> cnt(bit_length(total));
        const auto& update = [&](int x, int d, int curr) {
            for (int i = 0; (1 << i) <= x; ++i) {
                if (!(x & (1 << i))) {
                    continue;
                }
                if (cnt[i] == 0) {
                    curr ^= 1 << i;
                }
                cnt[i] += d;
                if (cnt[i] == 0) {
                    curr ^= 1 << i;
                }
            }
            return curr;
        };

        int result = size(nums);
        for (int right = 0, left = 0, curr = 0; right < size(nums); ++right) {
            curr = update(nums[right], +1, curr);
            for (; left <= right && curr >= k; ++left) {
                result = min(result, right - left + 1);
                curr = update(nums[left], -1, curr);
            }
        }
        return result;
    }


