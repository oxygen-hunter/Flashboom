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

    vector<int> timeTaken(vector<vector<int>>& edges) {
        vector<vector<int>> adj(size(edges) + 1);
        for (const auto& e : edges) {
            adj[e[0]].emplace_back(e[1]);
            adj[e[1]].emplace_back(e[0]);
        }
        vector<vector<pair<int, int>>> dp(size(edges) + 1, vector<pair<int, int>>(2, pair(0, -1)));
        const function<void (int, int)> dfs1 = [&](int u, int p) {
            for (const auto& v : adj[u]) {
                if (v == p) {
                    continue;
                }
                dfs1(v, u);
                pair<int, int> curr = pair((v % 2 ? 1 : 2) + dp[v][0].first, v);
                for (int i = 0; i < size(dp[u]); ++i) {
                    if (curr > dp[u][i]) {
                        swap(curr, dp[u][i]);
                    }
              }
            }
        };

        vector<int> result(size(edges) + 1);
        const function<void (int, int, int)> dfs2 = [&](int u, int p, int curr) {
            result[u] = max(dp[u][0].first, curr);
            for (const auto& v : adj[u]) {
                if (v == p) {
                    continue;
                }
                dfs2(v, u, (u % 2 ? 1 : 2) + max(dp[u][dp[u][0].second == v].first, curr));
            }
        };
    
        dfs1(0, -1);
        dfs2(0, -1, 0);
        return result;
    }

