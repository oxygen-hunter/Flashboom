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

    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {
        static const int INF = numeric_limits<int>::max();

        vector<vector<pair<int, int>>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].emplace_back(e[1], e[2]);
            adj[e[1]].emplace_back(e[0], e[2]);
        }
        const auto& dijkstra = [&](int start) {
            vector<int64_t> best(size(adj), INF);
            best[start] = 0;
            priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>, greater<pair<int64_t, int>>> min_heap;
            min_heap.emplace(0, start);
            while (!empty(min_heap)) {
                const auto [curr, u] = min_heap.top(); min_heap.pop();
                if (curr > best[u]) {
                    continue;
                }
                for (const auto& [v, w] : adj[u]) {
                    if (best[v] - curr <= w) {
                        continue;
                    }
                    best[v] = curr + w;
                    min_heap.emplace(best[v], v);
                }
            }
            return best;
        };

        const auto& dist1 = dijkstra(0);
        const auto& dist2 = dijkstra(n - 1);
        vector<bool> result(size(edges));
        int i = 0;
        for (const auto& e : edges) {
            result[i++] = (dist1[e[0]] != INF && dist2[e[1]] != INF && dist1[e[0]] + e[2] + dist2[e[1]] == dist1[n - 1]) ||
                          (dist2[e[0]] != INF && dist1[e[1]] != INF && dist2[e[0]] + e[2] + dist1[e[1]] == dist2[0]);
        } 
        return result;
    }

