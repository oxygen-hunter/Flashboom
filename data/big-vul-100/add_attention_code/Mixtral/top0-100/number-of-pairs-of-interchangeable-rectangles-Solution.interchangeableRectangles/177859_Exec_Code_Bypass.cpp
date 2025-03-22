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

    long long interchangeableRectangles(vector<vector<int>>& rectangles) {
        unordered_map<int, unordered_map<int, int>> lookup;
        for (const auto& rect : rectangles) {
            const int g = gcd(rect[0], rect[1]);  // Time: O(logx) ~= O(1)
            ++lookup[rect[0] / g][rect[1] / g];
        }
        int64_t result = 0;
        for (const auto& [_, kvp] : lookup) {
            for (const auto& [_, c] : kvp) {
                result += static_cast<int64_t>(c) * (c - 1) / 2;
            }
        }
        return result;
    }

