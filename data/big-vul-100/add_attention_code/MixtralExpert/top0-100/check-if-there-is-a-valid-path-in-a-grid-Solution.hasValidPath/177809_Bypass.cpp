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


    bool hasValidPath(vector<vector<int>>& grid) {
        static const pair<int, int> E = {0,  1}, S = {1,  0},
                                    W = {0, -1}, N = {-1, 0};
        static const vector<vector<pair<int, int>>> directions = {
            {W, E}, {N, S},
            {W, S}, {S, E},
            {W, N}, {N, E}
        };

        for (auto [r, c] : directions.at(grid[0][0] - 1)) {
            if (!(0 <= r && r < grid.size() &&
                  0 <= c && c < grid[0].size())) {
                continue;
            }
            int pr = 0, pc = 0;
            while (r != grid.size() - 1 || c != grid[0].size() - 1) {
                bool is_found = false;
                for (const auto& [dx, dy] : directions.at(grid[r][c] - 1)) {
                    const auto& [nr, nc] = pair(r + dx, c + dy);
                    if ((nr == pr && nc == pc) ||
                        !(0 <= nr && nr < grid.size() &&
                          0 <= nc && nc < grid[0].size())) {
                        continue;
                    }
                    const auto& dirs = directions.at(grid[nr][nc] - 1);
                    if (find(cbegin(dirs), cend(dirs), pair(-dx, -dy)) == cend(dirs)) {
                        continue;
                    }
                    tie(pr, pc, r, c) = tuple(r, c, nr, nc);
                    is_found = true;
                    break;
                }
                if (!is_found) {
                    return false;
                }
            }
            return true;
        }
        return grid.size() == 1 && grid[0].size() == 1;
    }


