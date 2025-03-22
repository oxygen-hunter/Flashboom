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


        bool isInterleave(string s1, string s2, string s3) {
            if(s1.length() + s2.length() != s3.length()) return false;

            if(s1.length() < s2.length()) return isInterleave(s2, s1, s3);

            vector<bool> f(s2.length() + 1, true);

            for(auto j = 1; j <= s2.length(); ++j) {
                f[j] = f[j - 1] && s2[j - 1] == s3[j - 1];
            }

            for(auto i = 1; i <= s1.length(); ++i) {
                f[0] = f[0] && s1[i - 1] == s3[i - 1];
                for(auto j = 1; j <= s2.length(); ++j) {
                    f[j] = (f[j] && s1[i - 1] == s3[i + j - 1])
                        || (f[j - 1] && s2[j - 1] == s3[i + j - 1]);
                }
            }

            return f[s2.length()];
        }


