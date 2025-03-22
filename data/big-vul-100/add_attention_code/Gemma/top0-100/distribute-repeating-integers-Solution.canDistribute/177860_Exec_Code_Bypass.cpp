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


    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        unordered_map<int, int> count;
        for(int i = 0; i < size(nums); ++i) {
            ++count[nums[i]];
        }
        int total = (1 << size(quantity)) - 1;
        vector<int> requirement(total + 1);
        for (int mask = 0; mask < size(requirement); ++mask) {  // Time: O(2^m)
            for (int i = 0; i < size(quantity); ++i) {  // Time: O(m)
                if (mask & (1 << i)) {
                    requirement[mask] += quantity[i];
                }
            }
        }
        vector<vector<int>> dp(2, vector<int>(total + 1));
        dp[0][0] = 1;
        int i = 0;
        vector<int> cnts;
        for (const auto& [_, cnt] : count) {
            cnts.emplace_back(cnt);
        }
        if (size(quantity) < size(cnts)) {  // at most use top m cnts
            nth_element(begin(cnts), begin(cnts) + size(quantity) - 1, end(cnts), greater<int>());
            cnts.resize(size(quantity));
        }
        for (int i = 0; i < size(cnts); ++i) {  // Time: O(m)
            dp[(i + 1) % 2] = vector<int>(total + 1);
            // submask enumeration:
            // => sum(nCr(m, k) * 2^k for k in xrange(m+1)) = (1 + 2)^m = 3^m
            // => Time: O(3^m), see https://cp-algorithms.com/algebra/all-submasks.html
            for (int mask = total; mask >= 0; --mask) {
                dp[(i + 1) % 2][mask] |= dp[i % 2][mask];
                for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
                    if (requirement[submask] <= cnts[i] && dp[i % 2][mask ^ submask]) {
                        dp[(i + 1) % 2][mask] = 1;
                    }
                }
            }
        }
        return dp[size(cnts) % 2][total];
    }


