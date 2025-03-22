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

    int minOperations(vector<int>& nums) {
        static const int INF = numeric_limits<int>::max();

        const int cnt = count(cbegin(nums), cend(nums), 1);
        if (cnt) {
            return size(nums) - cnt;
        }
        int result = INF;
        for (int i = 0; i < size(nums); ++i) {
            int g = nums[i];
            for (int j = i + 1; j < size(nums); ++j) {
                g = gcd(g, nums[j]);
                if (g == 1) {
                    result = min(result, j - i);
                    break;
                }
            }
        }
        return result != INF ? result + (size(nums) - 1) : -1;
    }

