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

    string shortestCommonSupersequence(string str1, string str2) {
        vector<vector<int>> dp(2, vector<int>(str2.size() + 1));
        vector<vector<tuple<int, int, char>>> bt(str1.size() + 1,
                                                 vector<tuple<int, int, char>>(str2.size() + 1));
        for (int i = 0; i < str1.length(); ++i) {
            bt[i + 1][0] = {i, 0, str1[i]};
        }
        for (int j = 0; j < str2.length(); ++j) {
            bt[0][j + 1] = {0, j, str2[j]};
        }
        for (int i = 0; i < str1.length(); ++i) {
            for (int j = 0; j < str2.length(); ++j) {
                if (dp[i % 2][j + 1] > dp[(i + 1) % 2][j]) {
                    dp[(i + 1) % 2][j + 1] = dp[i % 2][j + 1];
                    bt[i + 1][j + 1] = {i, j + 1, str1[i]};
                } else {
                    dp[(i + 1) % 2][j + 1] = dp[(i + 1) % 2][j];
                    bt[i + 1][j + 1] = {i + 1, j, str2[j]};
                }
                if (str1[i] != str2[j]) {
                    continue;
                }
                if (dp[i % 2][j] + 1 > dp[(i + 1) % 2][j + 1]) {
                    dp[(i + 1) % 2][j + 1] = dp[i % 2][j] + 1;
                    bt[i + 1][j + 1] = {i, j, str1[i]};
                }
            }
        }
        
        int i = str1.length(), j = str2.length();
        char c = 0;
        string result;
        while (i != 0 || j != 0) {
            tie(i, j, c) = bt[i][j];
            result.push_back(c);
        }
        reverse(result.begin(), result.end());
        return result;
    }

