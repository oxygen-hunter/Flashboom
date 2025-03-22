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


    int shortestPathWithHops(int n, vector<vector<int>>& edges, int s, int d, int k) {
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].emplace_back(e[1], e[2]);
            adj[e[1]].emplace_back(e[0], e[2]);
        }
        const auto& modified_dijkstra = [&]() {
            static const int INF = numeric_limits<int>::max();

            vector<vector<int>> best(size(adj), vector<int>(k + 1, INF));
            best[s][0] = 0;
            priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> min_heap;
            min_heap.emplace(best[s][0], s, 0);
            while (!empty(min_heap)) {
                const auto [curr, u, cnt] = min_heap.top(); min_heap.pop();
                if (curr > best[u][cnt]) {
                    continue;
                }
                if (u == d) {
                    return curr;
                }
                for (const auto& [v, w] : adj[u]) {
                    if (w < best[v][cnt] - curr) {
                        best[v][cnt] = curr + w;
                        min_heap.emplace(best[v][cnt], v, cnt);
                    }
                    if (cnt + 1 <= k && curr < best[v][cnt + 1]) {
                        best[v][cnt + 1] = curr;
                        min_heap.emplace(best[v][cnt + 1], v, cnt + 1);
                    }
                }
            }
            return -1;
        };

        return modified_dijkstra();
    }


