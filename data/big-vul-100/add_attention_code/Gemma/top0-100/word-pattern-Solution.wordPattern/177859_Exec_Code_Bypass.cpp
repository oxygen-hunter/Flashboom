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


    bool wordPattern(string pattern, string str) {
        // Count the words.
        int cnt = str.empty() ? 0 : 1;
        for (const auto& c : str) {
            if (c == ' ') {
                ++cnt;
            }
        }
        if (pattern.size() != cnt) {
            return false;
        }

        unordered_map<string, char> w2p;
        unordered_map<char, string> p2w;
        int i = 0, j = 0;
        for (const auto& p : pattern) {
            // Get a word at a time without saving all the words.
            j = str.find(" ", i);
            if (j == string::npos) {
                j = str.length();
            }
            const string w = str.substr(i, j - i);
    
            if (!w2p.count(w) && !p2w.count(p)) { 
                // Build mapping. Space: O(c)
                w2p[w] = p; 
                p2w[p] = w; 
            } else if (!w2p.count(w) || w2p[w] != p) {
                // Contradict mapping.
                return false;
            }
            i = j + 1;
        }
        return true;
    }


