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


    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        vector<int64_t> diffs(size(nums1));
        for (int i = 0; i < size(diffs); ++i) {
            diffs[i] = abs(nums1[i] - nums2[i]);
        }
        sort(rbegin(diffs), rend(diffs));
        int64_t k = min(static_cast<int64_t>(k1) + k2, accumulate(cbegin(diffs), cend(diffs), static_cast<int64_t>(0)));
        const auto& check = [&](int x) {
            return accumulate(cbegin(diffs), cend(diffs), 0ll,
                              [&](const auto& total, const auto& d) {
                                  return total + max(d - x, static_cast<int64_t>(0));
                              }) <= k;
        };
        int64_t left = 0, right = diffs[0];
        while (left <= right) {
            const int mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        k -= accumulate(cbegin(diffs), cend(diffs), 0ll,
                        [&](const auto& total, const auto& d) {
                            return total + max(d - left, static_cast<int64_t>(0));
                        });
        for (int i = 0; i < size(diffs); ++i) {
            diffs[i] = min(diffs[i], left) - int(i < k);
        }
        return accumulate(cbegin(diffs), cend(diffs), 0ll,
                          [](const auto& total, const auto& d) {
                              return total + d * d;
                          });
    }


