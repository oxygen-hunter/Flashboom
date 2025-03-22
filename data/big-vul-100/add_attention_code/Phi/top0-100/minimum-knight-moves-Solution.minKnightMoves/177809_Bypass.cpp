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

    int minKnightMoves(int x, int y) {
        // we can observe from:
        // [0]
        // [3, 2]
        // [2,(1),4]
        // [3, 2, 3, 2]
        // [2, 3,(2) 3, 4]
        // [3, 4, 3, 4, 3, 4]
        // [4, 3, 4,(3),4, 5, 4]
        // [5, 4, 5, 4, 5, 4, 5, 6]
        // [4, 5, 4, 5,(4),5, 6, 5, 6]
        // [5, 6, 5, 6, 5, 6, 5, 6, 7, 6]
        // [6, 5, 6, 5, 6,(5),6, 7, 6, 7, 8]
        // [7, 6, 7, 6, 7, 6, 7, 6, 7, 8, 7, 8]
        // [6, 7, 6, 7, 6, 7,(6),7, 8, 7, 8, 9, 8]
        // [7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 9, 8, 9, 10]
        // [8, 7, 8, 7, 8, 7, 8,(7),8, 9, 8, 9, 10, 9, 10]
        // [9, 8, 9, 8, 9, 8, 9, 8, 9, 8, 9, 10, 9, 10, 11, 10]

        x = abs(x), y = abs(y);
        if (x < y) {
            swap(x, y);
        }
        static const unordered_map<pair<int, int>, int, PairHash<int>> lookup =
            {{{1, 0}, 3}, {{2, 2}, 4}};  // special cases
        if (lookup.count({x, y})) {
            return lookup.at({x, y});
        }
        const auto& k = x - y;
        if (y > k) {
            // if 2y > x, every period 3 of y (or k) with fixed another is increased by 2 (or 1)
            // and start from (2k, k) with (k) when y = k (diagonal line)
            // ex. (0, 0) ~ (12, 12) ~ ... : 0 => 2,4(special case),2 => 4,4,4 => 6,6,6 => 8,8,8 => ...
            // ex. (2, 1) ~ (14, 13) ~ ... : 1 => 3,3,3 => 5,5,5 => 7,7,7 => 9,9,9 => ...
            return k + 2 * ((y - k - 1) / 3 + 1);
        }
        // if 2y <= x, every period 4 of k (or y) with fixed another is increased by 2
        // and start from (2k, k) with (k) when y = k (vertical line)
        // ex. (0, 0) ~ (11, 0) ~ ... : 0,3(special case),2,3 => 2,3,4,5 => 4,5,6,7 => ...
        // ex. (2, 1) ~ (13, 1) ~ ... : 1,2,3,4 => 3,4,5,6 => 5,6,7,8 => ...
        return k - 2 * ((k - y) / 4);
    }

