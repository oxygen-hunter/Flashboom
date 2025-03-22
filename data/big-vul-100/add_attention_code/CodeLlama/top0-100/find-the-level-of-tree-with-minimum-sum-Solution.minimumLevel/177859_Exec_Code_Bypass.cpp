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


    int minimumLevel(TreeNode* root) {
        static const int64_t INF = numeric_limits<int64_t>::max();

        vector<TreeNode *> q = {root};
        pair<int64_t, int64_t> result = {INF, INF};
        for (int64_t d = 1; !empty(q); ++d) {
            vector<TreeNode *> new_q;
            int64_t total = 0ll;
            for (const auto& u : q) {
                if (u->left) {
                    new_q.emplace_back(u->left);
                }
                if (u->right) {
                    new_q.emplace_back(u->right);
                }
                total += u->val;
            }
            result = min(result, pair(total, d));
            q = move(new_q);
        }
        return result.second;
    }


