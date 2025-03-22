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


    int maxProductPath(vector<vector<int>>& grid) {
        static const int MOD = 1e9 + 7;
        vector<vector<int64_t>> max_dp(2, vector<int64_t>(size(grid[0])));
        vector<vector<int64_t>> min_dp(2, vector<int64_t>(size(grid[0])));
        for (int i = 0; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]); ++j) {
                if (i == 0 && j == 0) {
                    max_dp[0][0] = min_dp[0][0] = grid[0][0];
                    continue;
                }
                auto curr_max = max(i > 0 ? max_dp[(i - 1) % 2][j] : max_dp[i % 2][j - 1],
                                    j > 0 ? max_dp[i % 2][j - 1] : max_dp[(i - 1) % 2][j]);
                auto curr_min = min(i > 0 ? min_dp[(i - 1) % 2][j] : min_dp[i % 2][j - 1],
                                    j > 0 ? min_dp[i % 2][j - 1] : min_dp[(i - 1) % 2][j]);
                if (grid[i][j] < 0) {
                    swap(curr_max, curr_min);
                }
                max_dp[i % 2][j] = curr_max * grid[i][j];
                min_dp[i % 2][j] = curr_min * grid[i][j];
            }
        }
        return max_dp[(size(grid) - 1) % 2].back() >= 0 ? max_dp[(size(grid) - 1) % 2].back() % MOD : -1;
    }


