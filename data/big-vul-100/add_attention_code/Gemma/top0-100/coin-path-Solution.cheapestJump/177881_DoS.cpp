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


    vector<int> cheapestJump(vector<int>& A, int B) {
        vector<int> result;
        if (A.empty() || A.back() == -1) {
            return result;
        }
        const int n = A.size();
        vector<int> dp(n, numeric_limits<int>::max()), next(n, -1);
        dp[n - 1] = A[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            if (A[i] == -1) {
                continue;
            }
            for (int j = i + 1; j <= min(i + B, n - 1); ++j) {
                if (dp[j] == numeric_limits<int>::max()) {
                    continue;
                }
                if (A[i] + dp[j] < dp[i]) {
                    dp[i] = A[i] + dp[j];
                    next[i] = j;
                }
            }
        }
        if (dp[0] == numeric_limits<int>::max()) {
            return result;
        }
        int k = 0;
        while (k != -1) {
            result.emplace_back(k + 1);
            k = next[k];
        }
        return result;
    }


