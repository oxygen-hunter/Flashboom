struct edid *drm_load_edid_firmware(struct drm_connector *connector)
{
	const char *connector_name = connector->name;
	char *edidname, *last, *colon, *fwstr, *edidstr, *fallback = NULL;
	struct edid *edid;

	if (edid_firmware[0] == '\0')
		return ERR_PTR(-ENOENT);

	/*
	 * If there are multiple edid files specified and separated
	 * by commas, search through the list looking for one that
	 * matches the connector.
	 *
	 * If there's one or more that doesn't specify a connector, keep
 	 * the last one found one as a fallback.
 	 */
 	fwstr = kstrdup(edid_firmware, GFP_KERNEL);
 	edidstr = fwstr;
 
 	while ((edidname = strsep(&edidstr, ","))) {
			if (strncmp(connector_name, edidname, colon - edidname))
				continue;
			edidname = colon + 1;
			break;
		}

		if (*edidname != '\0') /* corner case: multiple ',' */
			fallback = edidname;
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

