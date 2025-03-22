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


    vector<vector<int>> resultGrid(vector<vector<int>>& image, int threshold) {
        const auto& check = [&](int i, int j) {
            for (int ni = i - 1; ni <= i; ++ni) {
                for (int nj = j - 1; nj <= j + 1; ++nj) {
                    if (abs(image[ni][nj] - image[ni + 1][nj]) > threshold) {
                        return false;
                    }
                }
            }
            for (int ni = i - 1; ni <= i + 1; ++ni) {
                for (int nj = j - 1; nj <= j; ++nj) {
                    if (abs(image[ni][nj] - image[ni][nj + 1]) > threshold) {
                        return false;
                    }
                }
            }
            return true;
        };
    
        vector<vector<int>> result(size(image), vector<int>(size(image[0])));
        vector<vector<int>> cnt(size(image), vector<int>(size(image[0])));
        for (int i = 1; i + 1 < size(image); ++i) {
            for (int j = 1; j + 1 < size(image[0]); ++j) {
                if (!check(i, j)) {
                    continue;
                }
                int total = 0;
                for (int ni = i - 1; ni <= i + 1; ++ni) {
                    for (int nj = j - 1; nj <= j + 1; ++nj) {
                        total += image[ni][nj];
                    }
                }
                total /= 9;
                for (int ni = i - 1; ni <= i + 1; ++ni) {
                    for (int nj = j - 1; nj <= j + 1; ++nj) {
                        ++cnt[ni][nj];
                        result[ni][nj] += total;
                    }
                }
            }
        }
        for (int i = 0; i < size(image); ++i) {
            for (int j = 0; j < size(image[0]); ++j) {
                if (cnt[i][j]) {
                    result[i][j] /= cnt[i][j];
                } else {
                    result[i][j] = image[i][j];
                }
            }
        }
        return result;
    }


