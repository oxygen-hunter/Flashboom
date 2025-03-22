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

    void gameOfLife(vector<vector<int>>& board) {
        const int m = board.size(), n = m ? board[0].size() : 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int count = 0;
                // Count live cells in 3x3 block.
                for (int I = max(i - 1, 0); I < min(i + 2, m); ++I) {
                    for (int J = max(j - 1, 0); J < min(j + 2, n); ++J) {
                        count += board[I][J] & 1;
                    }
                }
                // if (count == 4 && board[i][j]) means:
                //     Any live cell with three live neighbors lives.
                // if (count == 3) means:
                //     Any live cell with two live neighbors.
                //     Any dead cell with exactly three live neighbors lives.
                if ((count == 4 && board[i][j]) || count == 3) {
                    board[i][j] |= 2;  // Mark as live. 
                }
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] >>= 1;  // Update to the next state.
            }
        }
    }

