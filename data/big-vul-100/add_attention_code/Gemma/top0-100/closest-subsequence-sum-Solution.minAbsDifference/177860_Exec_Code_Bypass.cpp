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


    int minAbsDifference(vector<int>& nums, int goal) {
        int mx = 0, mn = 0;
        for (const auto& x : nums) {
            if (x > 0) {
                mx += x;
            } else if (x < 0) {
                mn += x;
            }
        }
        if (goal > mx) {
            return goal - mx;
        }
        if (goal < mn) {
            return mn - goal;
        }
        int result = abs(goal);
        unordered_set<int> sums1{0};
        for (auto i = 0; i < size(nums) / 2; ++i) {
            for (const auto& x : vector<int>(cbegin(sums1), cend(sums1))) {
                if (!sums1.emplace(x + nums[i]).second) {
                    continue;
                }
                result = min(result, abs(goal - x - nums[i]));  // case of right half part is 0
            }
        }
        vector<int> sorted_sums1(cbegin(sums1), cend(sums1));  // Space: O(2^(n/2))
        sort(begin(sorted_sums1), end(sorted_sums1));  // Time: O((n/2) * 2^(n/2)) = O(n * 2^(n/2))
        unordered_set<int> sums2{0};
        for (int i = size(nums) / 2; i < size(nums); ++i) {
            for (const auto& x : vector<int>(cbegin(sums2), cend(sums2))) {
                if (!sums2.emplace(x + nums[i]).second) {
                    continue;
                }
                auto cit = lower_bound(cbegin(sorted_sums1), cend(sorted_sums1), goal - x - nums[i]);  // Time: O(2^(n/2)) * O(n/2)
                if (cit != cend(sorted_sums1)) {
                    result = min(result, abs(goal - x - nums[i] - *cit));
                }
                if (cit != cbegin(sorted_sums1)) {
                    result = min(result, abs(goal - x - nums[i] - *prev(cit)));
                }
                if (result == 0) {
                    return result;
                }
            }
        }
        return result;
    }


