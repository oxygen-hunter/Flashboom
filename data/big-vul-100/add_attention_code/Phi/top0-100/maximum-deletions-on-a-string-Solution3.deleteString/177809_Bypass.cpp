restore_page_device(i_ctx_t *i_ctx_p, const gs_gstate * pgs_old, const gs_gstate * pgs_new)
{
    gx_device *dev_old = gs_currentdevice(pgs_old);
    gx_device *dev_new;
    gx_device *dev_t1;
    gx_device *dev_t2;
    bool samepagedevice = obj_eq(dev_old->memory, &gs_int_gstate(pgs_old)->pagedevice,
        &gs_int_gstate(pgs_new)->pagedevice);
    bool LockSafetyParams = dev_old->LockSafetyParams;

    if ((dev_t1 = (*dev_proc(dev_old, get_page_device)) (dev_old)) == 0)
        return 0;
    /* If we are going to putdeviceparams in a callout, we need to */
    /* unlock temporarily.  The device will be re-locked as needed */
    /* by putdeviceparams from the pgs_old->pagedevice dict state. */
    if (!samepagedevice)
        dev_old->LockSafetyParams = false;
    dev_new = gs_currentdevice(pgs_new);
    if (dev_old != dev_new) {
        if ((dev_t2 = (*dev_proc(dev_new, get_page_device)) (dev_new)) == 0)
            samepagedevice = true;
        else if (dev_t1 != dev_t2)
             samepagedevice = false;
     }
 
    if (LockSafetyParams && !samepagedevice) {
         const int required_ops = 512;
         const int required_es = 32;
        /* The %grestorepagedevice must complete: the biggest danger
           is operand stack overflow. As we use get/putdeviceparams
           that means pushing all the device params onto the stack,
           pdfwrite having by far the largest number of parameters
           at (currently) 212 key/value pairs - thus needing (currently)
           424 entries on the op stack. Allowing for working stack
           space, and safety margin.....
         */
        if (required_ops + ref_stack_count(&o_stack) >= ref_stack_max_count(&o_stack)) {
           gs_currentdevice(pgs_old)->LockSafetyParams = LockSafetyParams;
           return_error(gs_error_stackoverflow);
        }
        /* We also want enough exec stack space - 32 is an overestimate of
           what we need to complete the Postscript call out.
         */
        if (required_es + ref_stack_count(&e_stack) >= ref_stack_max_count(&e_stack)) {
           gs_currentdevice(pgs_old)->LockSafetyParams = LockSafetyParams;
           return_error(gs_error_execstackoverflow);
        }
    }
    /*
     * The current implementation of setpagedevice just sets new
     * parameters in the same device object, so we have to check
     * whether the page device dictionaries are the same.
     */
    return samepagedevice ? 0 : 1;
}

    int deleteString(string s) {
        static const int MOD = 1e9 + 7;
        static vector<int> P = {113, 109};
        if (all_of(cbegin(s), cend(s), [&](const auto& x) { return x == s[0]; })) {
            return size(s);
        }
        vector<vector<int64_t>> power(size(P), vector<int64_t>(1, 1));
        vector<vector<int64_t>> prefix(size(P), vector<int64_t>(1));
        const auto& hash = [&](int i, int j) {
            vector<int> h(size(P));
            for (int idx = 0; idx < size(P); ++idx) {
                h[idx] = ((prefix[idx][j + 1] - prefix[idx][i] * power[idx][j - i + 1]) % MOD + MOD) % MOD;
            }
            return h;
        };
        for (const auto& x : s) {
            for (int idx = 0; idx < size(P); ++idx) {
                power[idx].emplace_back(power[idx].back() * P[idx] % MOD);
                prefix[idx].emplace_back((prefix[idx].back() * P[idx] + (x - 'a')) % MOD);
            }
        }
        vector<int> dp(size(s), 1);  // dp[i]: max operation count of s[i:]
        for (int i = size(s) - 2; i >= 0; --i) {              
            for (int j = 1; j <= (size(s) - i) / 2 ; ++j) {
                if (hash(i, i + j - 1) == hash(i + j, i + 2 * j - 1)) {
                    dp[i] = max(dp[i], dp[i + j] + 1);
                }
            }
        }
        return dp[0];
    }

