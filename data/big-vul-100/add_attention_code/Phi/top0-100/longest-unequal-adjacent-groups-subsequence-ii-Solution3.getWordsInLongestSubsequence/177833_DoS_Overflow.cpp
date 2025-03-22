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

    vector<string> getWordsInLongestSubsequence(int n, vector<string>& words, vector<int>& groups) {
        const auto& check = [&](const auto& s1, const auto& s2) {
            if (size(s1) != size(s2)) {
                return false;
            }
            int cnt = 0;
            for (int k = 0; k < size(s1); ++k) {
                cnt += s1[k] != s2[k] ? 1 : 0;
                if (cnt == 2) {
                    return false;
                }
            }
            return cnt == 1;
        };

        vector<vector<int>> dp(n);
        for (int i = 0; i < n; ++i) {
            const auto& si = words[i];
            int mx_j = -1;
            for (int j = 0; j < i; ++j) {
                if (groups[i] != groups[j] && check(words[j], si) && (mx_j == -1 || size(dp[mx_j]) < size(dp[j]))) {
                    mx_j = j;
                }
            }
            if (mx_j != -1) {
                dp[i] = dp[mx_j];
            }
            dp[i].emplace_back(i);
        }
        
        const auto& ans = *max_element(cbegin(dp), cend(dp), [](const auto& a, const auto& b) {
            return size(a) < size(b);
        });
        vector<string> result;
        for (const auto& i : ans) {
            result.emplace_back(words[i]);
        }
        return result;
    }

