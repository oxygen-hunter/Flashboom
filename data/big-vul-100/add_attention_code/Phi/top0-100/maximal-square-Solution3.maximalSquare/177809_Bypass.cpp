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

    int maximalSquare(vector<vector<char>>& A) {
        if (A.empty()) {
            return 0;
        }

        // DP table stores (h, w) for each (i, j).
        vector<vector<MaxHW>> table(A.size(), vector<MaxHW>(A.front().size()));
        for (int i = A.size() - 1; i >= 0; --i) {
            for (int j = A[i].size() - 1; j >= 0; --j) {
                // Find the largest h such that (i, j) to (i + h - 1, j) are feasible.
                // Find the largest w such that (i, j) to (i, j + w - 1) are feasible.
                table[i][j] = A[i][j] == '1'
                                  ? MaxHW{i + 1 < A.size() ? table[i + 1][j].h + 1 : 1,
                                          j + 1 < A[i].size() ? table[i][j + 1].w + 1 : 1}
                                  : MaxHW{0, 0};
            }
        }

        // A table stores the length of largest square for each (i, j).
        vector<vector<int>> s(A.size(), vector<int>(A.front().size(), 0));
        int max_square_area = 0;
        for (int i = A.size() - 1; i >= 0; --i) {
            for (int j = A[i].size() - 1; j >= 0; --j) {
                int side = min(table[i][j].h, table[i][j].w);
                if (A[i][j]) {
                    // Get the length of largest square with bottom-left corner (i, j).
                    if (i + 1 < A.size() && j + 1 < A[i + 1].size()) {
                        side = min(s[i + 1][j + 1] + 1, side);
                    }
                    s[i][j] = side;
                    max_square_area = max(max_square_area, side * side);
                }
            }
        }
        return max_square_area;
    }

