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

    vector<int> mostSimilar(int n, vector<vector<int>>& roads, vector<string>& names, vector<string>& targetPath) {
        vector<vector<int>> adj(n);
        for (const auto& road : roads) {
            adj[road[0]].emplace_back(road[1]);
            adj[road[1]].emplace_back(road[0]);
        }

        vector<vector<int>> dp(targetPath.size() + 1, vector<int>(n));
        for (int i = 1; i <= targetPath.size(); ++i) {
            for (int v = 0; v < n; ++v) {
                dp[i][v] = targetPath.size();
                for (const auto& u : adj[v]) {
                    dp[i][v] = min(dp[i][v], dp[i - 1][u]);
                }
                dp[i][v] += int(names[v] != targetPath[i - 1]);
            }
        }

        vector<int> path = {static_cast<int>(distance(cbegin(dp.back()), 
                                                      min_element(cbegin(dp.back()), cend(dp.back()))))};
        for (int i = targetPath.size(); i >= 2; --i) {
            for (const auto& u : adj[path.back()]) {
                if (dp[i - 1][u] + int(names[path.back()] != targetPath[i - 1]) == dp[i][path.back()]) {
                    path.emplace_back(u);
                    break;
                }
            }
        }
        reverse(begin(path), end(path));
        return path;
    }

