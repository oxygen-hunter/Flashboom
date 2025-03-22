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


    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        vector<int> lookup(size(nums), -1);
        for (int i = size(changeIndices) - 1; i >= 0; --i) {
            if (nums[changeIndices[i] - 1]) {
                lookup[changeIndices[i] - 1] = i;
            }
        }
        const int64_t total = accumulate(cbegin(nums), cend(nums), 0ll) + size(nums);
        const auto& check = [&](int t) {
            priority_queue<int, vector<int>, greater<int>> min_heap;
            int64_t total2 = 0, cnt = 0;
            for (int i = t - 1; i >= 0; --i) {
                if (i != lookup[changeIndices[i] - 1]) {
                    ++cnt;
                    continue;
                }
                min_heap.emplace(nums[changeIndices[i] - 1]);
                total2 += nums[changeIndices[i] - 1];
                if (cnt) {
                    --cnt;
                } else {
                    ++cnt;
                    total2 -= min_heap.top(); min_heap.pop();
                }
            }
            return total - (total2 + (size(min_heap))) <= cnt;
        };
    
        int64_t total2 = 0;
        for (int i = 0; i < size(nums); ++i) {
            total2 += lookup[i] != -1 ? 1 : nums[i];
        }
        int64_t left = total2 + size(nums), right = size(changeIndices);
        while (left <= right) {
            const auto mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left <= size(changeIndices) ? left : -1;
    }


