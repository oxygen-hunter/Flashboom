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


    int minFlips(vector<vector<int>>& mat) {
        static const vector<pair<int, int>> directions{{0, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int start = 0;
        for (int r = 0; r < mat.size(); ++r) {
            for (int c = 0; c < mat[0].size(); ++c) {
                start |= mat[r][c] << r * mat[0].size() + c;
            }
        }
        queue<pair<int, int>> q({{start, 0}});
        unordered_set<int> lookup = {start};
        while (!q.empty()) {
            const auto [state, step] = q.front(); q.pop();
            if (!state) {
                return step;
            }
            for (int r = 0; r < mat.size(); ++r) {
                for (int c = 0; c < mat[0].size(); ++c) {
                    int new_state = state;
                    for (const auto& [dr, dc] : directions) {
                        const auto& [nr, nc] = make_pair(r + dr, c + dc);
                        if (0 <= nr && nr < mat.size() &&
                            0 <= nc && nc < mat[0].size()) {
                            new_state ^= 1 << nr * mat[0].size() + nc;
                        }
                    }
                    if (lookup.count(new_state)) {
                        continue;
                    }
                    lookup.emplace(new_state);
                    q.emplace(new_state, step + 1);
                 }
            }
        }
        return -1;
    }


