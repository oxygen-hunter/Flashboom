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


    int maxKilledEnemies(vector<vector<char>>& grid) {
        int result = 0;
        if (grid.empty() || grid[0].empty()) {
            return result;
        }

        vector<vector<int>> down{grid.size(), vector<int>(grid[0].size())};
        vector<vector<int>> right{grid.size(), vector<int>(grid[0].size())};
        for (int i = grid.size() - 1; i >= 0; --i) {
            for (int j = grid[0].size() - 1; j >= 0; --j) {
                if (grid[i][j] != 'W') {
                    if (i + 1 < grid.size()) {
                        down[i][j] = down[i + 1][j];
                    }
                    if (j + 1 < grid[0].size()) {
                        right[i][j] = right[i][j + 1];
                    }
                    if (grid[i][j] == 'E') {
                        ++down[i][j];
                        ++right[i][j];
                    }
                }
            }
        }

        int left = 0;
        vector<int> up(grid[0].size());
        for (int i = 0; i < grid.size(); ++i) {
            left = 0;
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == 'W') {
                    up[j] = 0;
                    left = 0;
                } else if (grid[i][j] == 'E') {
                    ++up[j];
                    ++left;
                } else {
                    result = max(result, left + up[j] + right[i][j] + down[i][j]);
                }
            }
        }

        return result;
    }


