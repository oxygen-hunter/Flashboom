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

    int minimumCost(int n, vector<vector<int>>& highways, int discounts) {
        using P = pair<int, int>;
        unordered_map<int, vector<P>> adj;
        for (const auto& highway : highways) {
            int u, v, w;
            tie(u, v, w) = make_tuple(highway[0], highway[1], highway[2]);
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        
        unordered_map<int, unordered_map<int, int>> best;
        best[0][discounts] = 0;
        using T = tuple<int, int, int>;
        priority_queue<T, vector<T>, greater<T>> min_heap;
        min_heap.emplace(0, 0, discounts);
        while (!empty(min_heap)) {
            auto [total, u, k] = min_heap.top(); min_heap.pop();
            if ((best.count(u) && best[u].count(k) &&  best[u][k] < total)) {
                continue;
            }
            if (u == n - 1) {
                return total;
            }
            for (const auto& [v, w] : adj[u]) {
                if (!best.count(v) ||
                    !best[v].count(k) ||
                    total + w < best[v][k]) {
                    best[v][k] = total + w;
                    min_heap.emplace(total + w, v, k);
                }
                if (k > 0 &&
                    (!best.count(v) ||
                    !best[v].count(k - 1) ||
                    total + w / 2 < best[v][k - 1])) {
                    best[v][k - 1] = total + w / 2;
                    min_heap.emplace(total + w / 2, v, k - 1);
                }
            }
        }
        return -1;
    }

