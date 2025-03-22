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

    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        const auto& ceil_divide = [](const auto& a, const auto& b) {
            return (a + b - 1) / 2;
        };

        const auto& tree_diameter = [](const auto& edges) {
            vector<vector<int>> adj(size(edges) + 1);
            for (const auto& e : edges) {
                adj[e[0]].emplace_back(e[1]);
                adj[e[1]].emplace_back(e[0]);
            }
            int result = 0;
            const auto& bfs = [&](int root) {
                int d = -1, new_root = -1;
                vector<bool> lookup(size(adj));
                lookup[root] = true;
                vector<int> q = {root};
                while (!empty(q)) {
                    ++d;
                    new_root = q[0];
                    vector<int> new_q;
                    for (const auto& u : q) {
                        for (const auto& v : adj[u]) {
                            if (lookup[v]) {
                                continue;
                            }
                            lookup[v] = true;
                            new_q.emplace_back(v);
                        }
                    }
                    q = move(new_q);
                }
                return pair(d, new_root);
            };

            const auto& [_, root] = bfs(0);
            const auto& [d, __] = bfs(root);
            return d;
        };

        const int d1 = tree_diameter(edges1);
        const int d2 = tree_diameter(edges2);
        return max({ceil_divide(d1, 2) + 1 + ceil_divide(d2, 2), d1, d2});
    }

