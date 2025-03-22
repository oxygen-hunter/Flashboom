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


    int minWastedSpace(vector<int>& packages, vector<vector<int>>& boxes) {
        static const int MOD = 1e9 + 7;
        static const int64_t INF = numeric_limits<int64_t>::max();

        sort(begin(packages), end(packages));
        int64_t result = INF;
        for (auto& box : boxes) {
            sort(begin(box), end(box));
            if (box.back() < packages.back()) {
                continue;
            }
            int64_t curr = 0;
            auto left = cbegin(packages);
            for (const auto& b : box) {
                auto right = upper_bound(left, cend(packages), b);
                curr += b * (right - left);
                left = right;
            }
            result = min(result, curr);
        }
        int64_t total = accumulate(cbegin(packages), cend(packages), 0LL);
        return result != INF ? (result - total) % MOD : -1;
    }


