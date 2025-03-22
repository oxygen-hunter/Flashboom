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


    bool hasNext() {
        while (!nodes_.empty()) {
            auto *cur = nodes_.top();
            if (cur->isInteger()) {
                return true;
            }
            nodes_.pop();
            auto& children = cur->getList();
            for (int i = static_cast<int>(children.size()) - 1; i >= 0; --i) {
                nodes_.emplace(&children[i]);
            }
        }
        return false;
    }


