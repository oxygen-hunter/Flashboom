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


    void addNum(int num) {
        // Balance smaller half and larger half.
        if (max_bst_.empty() || num > *max_bst_.cbegin()) {
            min_bst_.emplace(num);
            if (min_bst_.size() > max_bst_.size() + 1) {
                max_bst_.emplace(*min_bst_.cbegin());
                min_bst_.erase(min_bst_.cbegin());
            }
        } else {
            max_bst_.emplace(num);
            if (max_bst_.size() > min_bst_.size()) {
                min_bst_.emplace(*max_bst_.cbegin());
                max_bst_.erase(max_bst_.cbegin());
            }
        }
    }


