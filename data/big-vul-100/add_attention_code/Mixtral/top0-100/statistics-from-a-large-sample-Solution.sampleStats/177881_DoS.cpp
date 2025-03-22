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

    vector<double> sampleStats(vector<int>& count) {
        const double mi = distance(count.cbegin(), find_if(count.cbegin(), count.cend(), 
                                   [](int x) { return x != 0; }));
        
        const double ma = count.size() - 1 - 
                          distance(count.crbegin(), find_if(count.crbegin(), count.crend(), 
                                   [](int x) { return x != 0; }));
        
        const auto& n = accumulate(count.cbegin(), count.cend(), 0);
        double total = 0.0;
        for (int i = 0; i < count.size(); ++i) {
            total += double(i) * count[i];
        }
        const double mean = total / n;
        
        const double mode = distance(count.cbegin(), max_element(count.cbegin(), count.cend()));
        
        for (int i = 1; i < count.size(); ++i) {
            count[i] += count[i - 1];
        }
        const auto& median1 = distance(count.cbegin(), lower_bound(count.cbegin(), count.cend(), (n + 1) / 2));
        const auto& median2 = distance(count.cbegin(), lower_bound(count.cbegin(), count.cend(), (n + 2) / 2));
        const double median = (median1 + median2) / 2.0;
        
        return {mi, ma, mean, median, mode};
    }

