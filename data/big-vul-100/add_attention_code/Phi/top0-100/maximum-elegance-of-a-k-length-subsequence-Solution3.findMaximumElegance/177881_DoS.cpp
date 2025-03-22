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

    long long findMaximumElegance(vector<vector<int>>& items, int k) {
        sort(rbegin(items), rend(items));
        vector<bool> lookup(size(items));
        vector<int> stk;
        int64_t curr = 0, l = 0;
        for (int i = 0; i < k; ++i) {
            if (lookup[items[i][1] - 1]) {
                stk.emplace_back(items[i][0]);
            }
            curr += items[i][0];
            if (!lookup[items[i][1] - 1]) {
                lookup[items[i][1] - 1] = true;
                ++l;
            }
        }
        int64_t result = curr + l * l;
        for (int i = k; i < size(items); ++i) {
            if (lookup[items[i][1] - 1]) {
                continue;
            }
            if (empty(stk)) {
                break;
            }
            curr += items[i][0] - stk.back(); stk.pop_back();
            lookup[items[i][1] - 1] = true;
            ++l;
            result = max(result, curr + l * l);
        }
        return result;
    }

