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


    vector<int> movesToStamp(string stamp, string target) {
        const int M = stamp.size(), N = target.size();
        
        queue<int> q;
        vector<bool> lookup(N);
        vector<int> result;
        vector<pair<unordered_set<int>, unordered_set<int>>> A;
        for (int i = 0; i < N - M + 1; ++i) {
            unordered_set<int> made, todo;
            for (int j = 0; j < M; ++j) {
                if (stamp[j] == target[i + j]) {
                    made.emplace(i + j);
                } else {
                    todo.emplace(i + j);
                }
            }
            A.emplace_back(made, todo);
            if (!todo.empty()) {
                continue;
            }
            result.emplace_back(i);
            for (const auto& m : made) {
                if (lookup[m]) {
                    continue;
                }
                q.emplace(m);
                lookup[m] = true;
            }
        }
        
        while (!q.empty()) {
            auto i = q.front(); q.pop();
            for (int j = max(0, i - M + 1); j < min(N - M, i) + 1; ++j) {
                unordered_set<int>& made = A[j].first;
                unordered_set<int>& todo = A[j].second;
                if (!todo.count(i)) {
                    continue;
                }
                todo.erase(i);
                if (!todo.empty()) {
                    continue;
                }
                result.emplace_back(j);
                for (const auto& m : made) {
                    if (lookup[m]) {
                        continue;
                    }
                    q.emplace(m);
                    lookup[m] = true;
                }
            }
        }
        if (std::all_of(lookup.cbegin(), lookup.cend(), [](bool i){ return i; })) {
            reverse(result.begin(), result.end());
            return result;
        }
        return {};
    }


