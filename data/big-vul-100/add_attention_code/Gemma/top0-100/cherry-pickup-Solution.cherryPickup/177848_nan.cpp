static NTSTATUS do_connect(TALLOC_CTX *ctx,
					const char *server,
					const char *share,
					const struct user_auth_info *auth_info,
					bool show_sessetup,
					bool force_encrypt,
					int max_protocol,
					int port,
					int name_type,
					struct cli_state **pcli)
{
	struct cli_state *c = NULL;
	char *servicename;
	char *sharename;
	char *newserver, *newshare;
	const char *username;
	const char *password;
        const char *domain;
        NTSTATUS status;
        int flags = 0;
 
        /* make a copy so we don't modify the global string 'service' */
        servicename = talloc_strdup(ctx,share);
		sharename += 2;
		if (server == NULL) {
			server = sharename;
		}
		sharename = strchr_m(sharename,'\\');
		if (!sharename) {
			return NT_STATUS_NO_MEMORY;
		}
		*sharename = 0;
		sharename++;
	}


    int cherryPickup(vector<vector<int>>& grid) {
        // dp holds the max # of cherries two k-length paths can pickup.
        // The two k-length paths arrive at (i, k - i) and (j, k - j), 
        // respectively.
        const int n = grid.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        dp[0][0] = grid[0][0];

        const int max_len = 2 * (n - 1);
        for (int k = 1; k <= max_len; ++k) {
            for (int i = min(k, n - 1); i >= max(0, k - n + 1); --i) {  // 0 <= i < n, 0 <= k-i < n
                for (int j = min(k , n - 1); j >= i; --j) {             // i <= j < n, 0 <= k-j < n
                    if (grid[i][k - i] == -1 ||
                        grid[j][k - j] == -1) {
                        dp[i][j] = -1;
                        continue;
                    }
                    int cnt = grid[i][k - i] + ((i == j) ? 0 : grid[j][k - j]);
                    int max_cnt = -1;
                    static const vector<pair<int, int>> directions{{0, 0}, {-1, 0}, {0, -1}, {-1, -1}};
                    for (const auto& direction : directions) {
                        const auto ii = i + direction.first;
                        const auto jj = j + direction.second;
                        if (ii >= 0 && jj >= 0 && dp[ii][jj] >= 0) {
                            max_cnt = max(max_cnt, dp[ii][jj] + cnt);
                        }
                    }
                    dp[i][j] = max_cnt;
                }
            }
        }
        return max(dp[n - 1][n - 1], 0);
    }


