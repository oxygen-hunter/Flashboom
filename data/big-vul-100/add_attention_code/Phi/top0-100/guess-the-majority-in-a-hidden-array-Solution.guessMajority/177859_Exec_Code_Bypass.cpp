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

    int guessMajority(ArrayReader &reader) {
        int count_a = 1, count_b = 0, idx_b = -1;
        const auto& value_0_1_2_3 = reader.query(0, 1, 2, 3);
        int value_0_1_2_i = -1;
        for (int i = reader.length() - 1; i >= 4; --i) {
            value_0_1_2_i = reader.query(0, 1, 2, i);
            if (value_0_1_2_i == value_0_1_2_3) {  // nums[i] == nums[3]
                ++count_a;
            } else {
                ++count_b;
                idx_b = i;
            }
        }
        const auto& value_0_1_2_4 = value_0_1_2_i;
        for (int i = 0; i < 3; ++i) {
            vector<int> a_b;
            for (int j = 0; j < 3; ++j) {
                if (j == i) {
                    continue;
                }
                a_b.emplace_back(j);
            }
            const auto& value_a_b_3_4 = reader.query(a_b[0], a_b[1], 3, 4);
            if (value_a_b_3_4 == value_0_1_2_4) {  // nums[i] == nums[3]
                ++count_a;
            } else {
                ++count_b;
                idx_b = i;
            }
        }
        if (count_a == count_b) {
            return -1;
        }
        return count_a > count_b ? 3 : idx_b;
    }

