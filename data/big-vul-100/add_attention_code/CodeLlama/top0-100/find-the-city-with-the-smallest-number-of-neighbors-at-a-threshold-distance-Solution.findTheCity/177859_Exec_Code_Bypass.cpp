 gs_nulldevice(gs_gstate * pgs)
 {
     int code = 0;
     if (pgs->device == 0 || !gx_device_is_null(pgs->device)) {
         gx_device *ndev;
         code = gs_copydevice(&ndev, (const gx_device *)&gs_null_device,
                                 pgs->memory);
 
         if (code < 0)
             return code;
         /*
          * Internal devices have a reference count of 0, not 1,
          * aside from references from graphics states.
           to sort out how the icc profile is best handled with this device.
           It seems to inherit properties from the current device if there
           is one */
        rc_init(ndev, pgs->memory, 0);
        if (pgs->device != NULL) {
            if ((code = dev_proc(pgs->device, get_profile)(pgs->device,
                                               &(ndev->icc_struct))) < 0)
                return code;
            rc_increment(ndev->icc_struct);
            set_dev_proc(ndev, get_profile, gx_default_get_profile);
        }

        if ((code = gs_setdevice_no_erase(pgs, ndev)) < 0)
 
         if ((code = gs_setdevice_no_erase(pgs, ndev)) < 0)
             gs_free_object(pgs->memory, ndev, "gs_copydevice(device)");
     }
     return code;
 }


    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>> dist(n, vector<int>(n, numeric_limits<int>::max()));
        for (const auto& e : edges) {
            dist[e[0]][e[1]] = dist[e[1]][e[0]] = e[2];
        }
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
        }
        for (int k = 0; k < n; ++k) {
             for (int i = 0; i < n; ++i) {
                 for (int j = 0; j < n; ++j) {
                     if (dist[i][k] != numeric_limits<int>::max() &&
                         dist[k][j] != numeric_limits<int>::max()) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                     }
                 }
             }
        }
        int result = -1, min_num = numeric_limits<int>::max();
        for (int i = n - 1; i >= 0; --i) {
            int num = accumulate(dist[i].cbegin(), dist[i].cend(), 0,
                                 [&distanceThreshold](const auto& a, const auto& b) {
                                     return a + (b <= distanceThreshold);
                                 });
            if (num < min_num) {
                min_num = num;
                result = i;
            }
        }
        return result;
    }


