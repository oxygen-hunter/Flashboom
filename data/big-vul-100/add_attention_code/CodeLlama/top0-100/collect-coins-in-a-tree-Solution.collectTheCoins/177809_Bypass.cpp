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


    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        static const int DISTANCE = 2;

        vector<unordered_set<int>> adj(size(coins));
        for (const auto& e : edges) {
            adj[e[0]].emplace(e[1]);
            adj[e[1]].emplace(e[0]);
        }
        int n = size(coins);
        for (int i = 0; i < size(coins); ++i) {
            int u = i;
            while (size(adj[u]) == 1 && !coins[u]) {
                const int v = *cbegin(adj[u]);
                adj[u].erase(v);
                adj[v].erase(u);
                --n;
                u = v;
            }
        }
        vector<int> q;
        for (int u = 0; u < size(coins); ++u) {
            if (size(adj[u]) == 1) {
                q.emplace_back(u);
            }
        }
        for (int _ = 0; _ < DISTANCE; ++_) {
            vector<int> new_q;
            for (const auto& u : q) {
                if (empty(adj[u])) {
                    assert(n == 1);
                    break;
                }
                const int v = *cbegin(adj[u]);
                adj[u].erase(v);
                adj[v].erase(u);
                --n;
                if (size(adj[v]) == 1) {
                    new_q.emplace_back(v);
                }
            }
            q = move(new_q);
        }
        return (n - 1) * 2;
    }


