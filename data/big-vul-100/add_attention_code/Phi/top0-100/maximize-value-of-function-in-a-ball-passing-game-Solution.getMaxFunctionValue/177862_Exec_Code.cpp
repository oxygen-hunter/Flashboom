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

    long long getMaxFunctionValue(vector<int>& receiver, long long k) {
        const auto& find_cycles = [](const auto& adj) {
            vector<pair<int, int>> result;
            vector<int> lookup(size(adj));
            for (int i = 0, idx = 0; i < size(adj); ++i) {
                int u = i, prev = idx;
                while (!lookup[u]) {
                    lookup[u] = ++idx;
                    u = adj[u];
                }
                if (lookup[u] > prev) {
                    result.emplace_back(u, idx - lookup[u] + 1);
                }
            }
            return result;
        };
        
        const auto& cycles = find_cycles(receiver);
        vector<pair<int, int>> lookup(size(receiver), {-1, -1});
        vector<vector<int64_t>> prefixes(size(cycles), vector<int64_t>(1));
        const auto& find_prefixes = [&](const auto& cycles) {
            for (int idx = 0; idx < size(cycles); ++idx) {
                auto [u, l] = cycles[idx];
                for (int i = 0; i < l; ++i) {
                    lookup[u] = {idx, i};
                    prefixes[idx].emplace_back(prefixes[idx][i] + u);
                    u = receiver[u];
                }
            }
        };
        
        const auto& get_sum = [](const auto& prefix, int64_t i, int64_t cnt) {
            const int64_t l = size(prefix) - 1;
            const int64_t q = cnt / l;
            const int64_t r = cnt % l;
            return (q * prefix.back() +
                    (prefix[min(i + r, l)] - prefix[i]) +
                    (prefix[max((i + r) - l, static_cast<int64_t>(0))] - prefix[0]));
        };
        
        const auto& start_inside_cycle = [&]() {
            int64_t result = 0;
            for (auto [u, l] : cycles) {
                for (int _ = 0; _ < l; ++_) {
                    const auto& [idx, i] = lookup[u];
                    result = max(result, get_sum(prefixes[idx], i, k + 1));
                    u = receiver[u];
                }
            }
            return result;
        };
    
        const auto& start_outside_cycle = [&]() {
            int64_t result = 0;
            vector<int> degree(size(receiver));
            for (const auto& x : receiver) {
                ++degree[x];
            }
            for (int u = 0; u < size(receiver); ++u) {
                if (degree[u]) {
                    continue;
                }
                int64_t curr = 0;
                deque<int> dq;
                int v = u;
                while (lookup[v].first == -1) {
                    curr += v;
                    dq.emplace_back(v);
                    if (size(dq) == k + 1) {
                        result = max(result, curr);
                        curr -= dq.front(); dq.pop_front();
                    }
                    v = receiver[v];
                }
                const auto& [idx, i] = lookup[v];
                while (!empty(dq)) {
                    result = max(result, curr + get_sum(prefixes[idx], i, (k + 1) - size(dq)));
                    curr -= dq.front(); dq.pop_front();
                }
            }
            return result;
        };
              
        find_prefixes(cycles);
        return max(start_inside_cycle(), start_outside_cycle());
    }

