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


    vector<int> gridIllumination(int N, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
        unordered_set<int64_t> lookup;
        unordered_map<int, int> row, col, diag, anti;
        for (const auto& lamp : lamps) {
            int r, c;
            tie(r, c) = make_pair(lamp[0], lamp[1]);
            if (!lookup.emplace(static_cast<int64_t>(r) * N + c).second) {
                continue;
            }
            ++row[r];
            ++col[c];
            ++diag[r - c];
            ++anti[r + c];
        }
        
        vector<int> result;
        for (const auto& query : queries) {
            int r, c;
            tie(r, c) = make_pair(query[0], query[1]);
            if (!(row[r] || col[c] || diag[r - c] || anti[r + c])) {
                result.emplace_back(0);
                continue;
            }
            result.emplace_back(1);
            for (int nr = max(r - 1, 0); nr <= min(r + 1, N - 1); ++nr) {
                for (int nc = max(c - 1, 0); nc <= min(c + 1, N - 1); ++nc) {
                    if (!lookup.erase(static_cast<int64_t>(nr) * N + nc)) {
                        continue;
                    }
                    --row[nr];
                    --col[nc];
                    --diag[nr - nc];
                    --anti[nr + nc];
                }
            }
        }
        return result;
    }


