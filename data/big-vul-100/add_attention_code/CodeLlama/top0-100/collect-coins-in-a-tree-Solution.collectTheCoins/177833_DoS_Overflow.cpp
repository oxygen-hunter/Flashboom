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


    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        static const int DISTANCE = 2;

        vector<unordered_set<int>> adj(size(coins));
        for (const auto& e : edges) {
            adj[e[0]].emplace(e[1]);
            adj[e[1]].emplace(e[0]);
        }
        int n = size(coins);
        for (int i = 0; i < size(coins); ++i) {
            int u = i;
            while (size(adj[u]) == 1 && !coins[u]) {
                const int v = *cbegin(adj[u]);
                adj[u].erase(v);
                adj[v].erase(u);
                --n;
                u = v;
            }
        }
        vector<int> q;
        for (int u = 0; u < size(coins); ++u) {
            if (size(adj[u]) == 1) {
                q.emplace_back(u);
            }
        }
        for (int _ = 0; _ < DISTANCE; ++_) {
            vector<int> new_q;
            for (const auto& u : q) {
                if (empty(adj[u])) {
                    assert(n == 1);
                    break;
                }
                const int v = *cbegin(adj[u]);
                adj[u].erase(v);
                adj[v].erase(u);
                --n;
                if (size(adj[v]) == 1) {
                    new_q.emplace_back(v);
                }
            }
            q = move(new_q);
        }
        return (n - 1) * 2;
    }


