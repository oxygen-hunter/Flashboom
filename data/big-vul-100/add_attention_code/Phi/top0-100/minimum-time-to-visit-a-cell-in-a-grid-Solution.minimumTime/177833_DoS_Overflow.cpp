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

    int minimumTime(vector<vector<int>>& grid) {
        static const vector<pair<int, int>> DIRECTIONS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        if (min(grid[0][1], grid[1][0]) > 1) {
            return -1;
        }
        const auto& dijkstra = [&](const pair<int, int>& start, const pair<int, int>& target) {
            vector<vector<int>> best(size(grid), vector<int>(size(grid[0]), numeric_limits<int>::max()));
            best[start.first][start.second] = 0;
            using Data = tuple<int, int, int>;
            priority_queue<Data, vector<Data>, greater<Data>> min_heap;
            min_heap.emplace(0, start.first, start.second);
            while (!empty(min_heap)) {
                const auto [curr, i, j] = min_heap.top(); min_heap.pop();
                if (best[i][j] < curr) {
                    continue;
                }
                if (pair(i, j) == target) {
                    break;
                }
                for (const auto& [di, dj] : DIRECTIONS) {
                    const auto ni = i + di, nj = j + dj;
                    if (!(0 <= ni && ni < size(grid) &&
                          0 <= nj && nj < size(grid[0]) &&
                          best[ni][nj] > max(grid[ni][nj] + static_cast<int>(grid[ni][nj] % 2 == curr % 2), curr + 1))) {
                        continue;
                    }
                    best[ni][nj] = max(grid[ni][nj] + static_cast<int>(grid[ni][nj] % 2 == curr % 2), curr + 1);
                    min_heap.emplace(best[ni][nj], ni, nj);
                }
            }
            return best[target.first][target.second];
        };

        return dijkstra(pair(0, 0), pair(size(grid) - 1, size(grid[0]) - 1));
    }

