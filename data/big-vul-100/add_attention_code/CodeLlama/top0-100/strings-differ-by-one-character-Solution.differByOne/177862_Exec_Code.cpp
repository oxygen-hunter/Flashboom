restore_page_device(const gs_gstate * pgs_old, const gs_gstate * pgs_new)
 {
     gx_device *dev_old = gs_currentdevice(pgs_old);
     gx_device *dev_new;
    gx_device *dev_t1;
     gx_device *dev_t2;
     bool samepagedevice = obj_eq(dev_old->memory, &gs_int_gstate(pgs_old)->pagedevice,
         &gs_int_gstate(pgs_new)->pagedevice);
 
     if ((dev_t1 = (*dev_proc(dev_old, get_page_device)) (dev_old)) == 0)
        return false;
     /* If we are going to putdeviceparams in a callout, we need to */
     /* unlock temporarily.  The device will be re-locked as needed */
     /* by putdeviceparams from the pgs_old->pagedevice dict state. */
        dev_old->LockSafetyParams = false;
    dev_new = gs_currentdevice(pgs_new);
     dev_new = gs_currentdevice(pgs_new);
     if (dev_old != dev_new) {
         if ((dev_t2 = (*dev_proc(dev_new, get_page_device)) (dev_new)) == 0)
            return false;
        if (dev_t1 != dev_t2)
            return true;
     }
     /*
      * The current implementation of setpagedevice just sets new
      * parameters in the same device object, so we have to check
      * whether the page device dictionaries are the same.
      */
    return !samepagedevice;
 }


    bool differByOne(vector<string>& dict) {
        static const int MOD = 1e9 + 7;
        static const int64_t P = 113;

        vector<int> hashes(dict.size());
        for (int i = 0; i < dict.size(); ++i) {
            for (const auto& c : dict[i]) {
                hashes[i] = (P * hashes[i] + (c - 'a')) % MOD;
            }
        }

        int64_t base = 1;
        for (int p = dict[0].length() - 1; p >= 0; --p) {
            unordered_map<int, vector<int>> lookup;
            for (int i = 0; i < dict.size(); ++i) {
                int new_hash = ((hashes[i] - base * (dict[i][p] - 'a') % MOD) + MOD) % MOD;
                if (lookup.count(new_hash)) {
                    auto target = dict[i].substr(0, p);
                    target += dict[i].substr(p + 1);
                    for (const auto& j : lookup[new_hash]) {
                        auto candidate = dict[j].substr(0, p);
                        candidate += dict[j].substr(p + 1);
                        if (candidate == target) {
                            return true;
                        }
                    }
                }
                lookup[new_hash].emplace_back(i);
            }
            base = (P * base) % MOD;
        }
        return false;
    }


