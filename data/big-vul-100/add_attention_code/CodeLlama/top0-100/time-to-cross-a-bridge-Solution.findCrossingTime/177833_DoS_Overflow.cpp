 static void reds_handle_ticket(void *opaque)
 {
     RedLinkInfo *link = (RedLinkInfo *)opaque;
    char password[SPICE_MAX_PASSWORD_LENGTH];
     time_t ltime;
 
     time(&ltime);
    RSA_private_decrypt(link->tiTicketing.rsa_size,
                        link->tiTicketing.encrypted_ticket.encrypted_data,
                        (unsigned char *)password, link->tiTicketing.rsa, RSA_PKCS1_OAEP_PADDING);
 
     if (ticketing_enabled && !link->skip_auth) {
         int expired =  taTicket.expiration_time < ltime;
 
         if (strlen(taTicket.password) == 0) {
            reds_send_link_result(link, SPICE_LINK_ERR_PERMISSION_DENIED);
             spice_warning("Ticketing is enabled, but no password is set. "
                        "please set a ticket first");
            reds_link_free(link);
            return;
         }
 
        if (expired || strncmp(password, taTicket.password, SPICE_MAX_PASSWORD_LENGTH) != 0) {
             if (expired) {
                 spice_warning("Ticket has expired");
             } else {
                 spice_warning("Invalid password");
             }
            reds_send_link_result(link, SPICE_LINK_ERR_PERMISSION_DENIED);
            reds_link_free(link);
            return;
         }
     }
 
     reds_handle_link(link);
 }


    int findCrossingTime(int n, int k, vector<vector<int>>& time) {
        vector<pair<int, int>> workers;
        for (int i = 0; i < k; ++i) {
            workers.emplace_back(time[i][0] + time[i][2], i);
        }
        priority_queue<pair<int, int>> left_bridge(cbegin(workers), cend(workers)), right_bridge;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> left_ware, right_ware;
        int curr = 0;
        while (n) {
            while (!empty(left_ware) && left_ware.top().first <= curr) {
                const auto [_, i] = left_ware.top(); left_ware.pop();
                left_bridge.emplace(time[i][0] + time[i][2], i);
            }
            while (!empty(right_ware) && right_ware.top().first <= curr) {
                const auto [_, i] = right_ware.top(); right_ware.pop();
                right_bridge.emplace(time[i][0] + time[i][2], i);
            }
            if (!empty(right_bridge)) {
                const auto [_, i] = right_bridge.top(); right_bridge.pop();
                curr += time[i][2];
                left_ware.emplace(curr + time[i][3], i);
                --n;
            } else if (!empty(left_bridge) && n - size(right_ware)) {
                const auto [_, i] = left_bridge.top(); left_bridge.pop();
                curr += time[i][0];
                right_ware.emplace(curr + time[i][1], i);
            } else {
                curr = min(!empty(left_ware) ? left_ware.top().first : numeric_limits<int>::max(),
                           !empty(right_ware) ? right_ware.top().first : numeric_limits<int>::max());
            }
        }
        return curr;
    }


