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


    vector<int> findProductsOfElements(vector<vector<long long>>& queries) {
        const auto& binary_search = [](auto left, auto right, const auto& check) {
            while (left <= right) {
                const auto mid = left + ((right - left) / 2);
                if (check(mid)) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return left;
        };

        const auto& powmod = [&](auto a, auto b, int mod) {
            a %= mod;
            auto result = 1 % mod;
            while (b) {
                if (b & 1) {
                    result = result * a % mod;
                }
                a = a * a % mod;
                b >>= 1;
            }
            return result;
        };

        const auto& count1 = [&](auto x) {
            auto result = 0ll;
            for (int i = 0; (1ll << i) <= x; ++i) {
                const auto mask = (1ll << (i + 1)) - 1;
                result += ((x & ~mask) >> 1) + max((x & mask) - (1ll << i) + 1, 0ll);
            }
            return result;
        };
        
        const auto& count2 = [&](auto x) {
            auto result = 0ll;
            for (int i = 0; (1ll << i) <= x; ++i) {
                const auto mask = (1ll << (i + 1)) - 1;
                result += (((x & ~mask) >> 1) + max((x & mask) - (1ll << i) + 1, 0ll)) * i;
            }
            return result;
        };
    
        const auto& f = [&](auto x) {
            const auto y = binary_search(1ll, x - 1, [&](auto i) {
                return count1(i) >= x;
            });
            auto result = count2(y - 1);
            x -= count1(y - 1);
            for (int i = 0; (1ll << i) <= y; ++i) {
                if ((y & (1ll << i)) == 0) {
                    continue;
                }
                result += i;
                if (--x == 0) {
                    break;
                }
            }
            return result;
        };
    
        vector<int> result(size(queries));
        for (int i = 0; i < size(queries); ++i) {
            const auto left = queries[i][0], right = queries[i][1], mod = queries[i][2];
            result[i] =  powmod(2ll, f(right + 1) - f(left), mod);
        }
        return result;
    }


