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


    int checkWays(vector<vector<int>>& pairs) {
        unordered_map<int, unordered_set<int>> adj;
        for (const auto& pair : pairs) {
            adj[pair[0]].emplace(pair[1]);
            adj[pair[1]].emplace(pair[0]);
        }
        int n = size(adj);
        bool mul = false;
        unordered_set<int> lookup;
        vector<int> nodes;
        transform(begin(adj), end(adj), back_inserter(nodes),
                  [](const auto& kvp) { return kvp.first; });
        sort(begin(nodes), end(nodes),
             [&adj](const auto& a, const auto& b) {
                 return size(adj[a]) > size(adj[b]);
             });
        for (const auto& node : nodes) {
            lookup.emplace(node);
            int parent = 0;
            for (const auto& x : adj[node]) {
                if (!lookup.count(x)) {
                    continue;
                }
                if (parent == 0 || size(adj[x]) < size(adj[parent])) {
                    parent = x;
                }
            }
            if (parent) {
                for (const auto& x : adj[node]) {
                    if (x != parent && !adj[parent].count(x)) {
                        return 0;
                    }
                }
                mul |= size(adj[node]) == size(adj[parent]);
            } else if (size(adj[node]) != n - 1) {
                return 0;
            }
        }
        return 1 + mul;
    }


