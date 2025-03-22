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

    vector<vector<string>> mostPopularCreator(vector<string>& creators, vector<string>& ids, vector<int>& views) {
        unordered_map<string, int> cnt;
        unordered_map<string, pair<int, string>> lookup;
        for (int i = 0; i < size(creators); ++i) {
            cnt[creators[i]] += views[i];
            if (!lookup.count(creators[i])) {
                lookup[creators[i]] = {-views[i], ids[i]};
                continue;
            }
            lookup[creators[i]] = min(lookup[creators[i]], pair(-views[i], ids[i]));
        }
        int mx = 0;
        for (const auto& [_, v] : cnt) {
            mx = max(mx, v);
        }
        vector<vector<string>> result;
        for (const auto& [k, v] : cnt) {
            if (v != mx) {
                continue;
            }
            result.push_back({k, lookup[k].second});
        }
        return result;
    }

