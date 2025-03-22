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


    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        static const int MOD = 1e9 + 7;
        uint64_t result = 0, s_sum = 0;
        vector<pair<int, int>> engineers;
        for (int i = 0; i < speed.size(); ++i) {
            engineers.emplace_back(efficiency[i], speed[i]);
        }
        sort(engineers.begin(), engineers.end(), greater<pair<int, int>>());
        priority_queue<int, vector<int>, greater<int>> min_heap;
        for (const auto& [e, s] : engineers) {
            s_sum += s;
            min_heap.emplace(s);
            if (min_heap.size() > k) {
                s_sum -= min_heap.top(); min_heap.pop();
            }
            result = max(result, s_sum * e);
        }
        return result % MOD;
    }


