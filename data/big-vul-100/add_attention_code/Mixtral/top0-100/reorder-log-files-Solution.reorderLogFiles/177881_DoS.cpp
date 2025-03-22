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

    vector<string> reorderLogFiles(vector<string>& logs) {
        auto pivot = stable_partition(logs.begin(), logs.end(),
                                      []( const auto& log ) {
                                          return isalpha(log.back());
                                      });
        sort(logs.begin(), pivot,
             [](const auto& a, const auto& b) {
                 int i = a.find_first_of(' '), j = b.find_first_of(' ');
                 return a.substr(i) != b.substr(j) ?
                            a.substr(i) < b.substr(j) :
                            a.substr(0, i) < b.substr(0, j);
             });
        return logs;
    }

