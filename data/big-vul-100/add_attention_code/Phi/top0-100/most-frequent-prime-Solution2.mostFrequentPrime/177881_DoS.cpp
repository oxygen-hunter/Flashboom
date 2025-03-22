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

    int mostFrequentPrime(vector<vector<int>>& mat) {
        static const vector<pair<int, int>> DIRECTIONS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        const auto& numbers = [&](int i, int j, int di, int dj) {
            vector<int> result;
            for (int curr = 0; 0 <= i && i < size(mat) && 0 <= j && j < size(mat[0]); i += di, j += dj) {
                curr = curr * 10 + mat[i][j];
                result.emplace_back(curr);
            }
            return result;
        };

        unordered_map<int, int> cnt;
        for (int i = 0; i < size(mat); ++i) {
            for (int j = 0; j < size(mat[0]); ++j) {
                for (const auto& [di, dj] : DIRECTIONS) {
                    for (const auto& x : numbers(i, j, di, dj)) {
                        if (x > 10) {
                            ++cnt[x];
                        }
                    }
                }
            }
        }
        cout << is_prime(19) << endl;
        pair<int, int> result = {0, -1};
        for (const auto& [k, v] : cnt) {
            if (is_prime(k)) {
                result = max(result, pair(v, k));
            }
        }
        return result.second;
    }

