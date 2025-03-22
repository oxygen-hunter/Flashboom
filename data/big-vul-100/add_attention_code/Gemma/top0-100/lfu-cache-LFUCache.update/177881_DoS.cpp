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


    void update(int key, int value) {
        int freq = 0;
        if (key_to_nodeit_.count(key)) {
            auto old_node = *key_to_nodeit_[key];        
            freq = std::get<FREQ>(old_node);
            freq_to_nodes_[freq].erase(key_to_nodeit_[key]);
            if (freq_to_nodes_[freq].empty()) {
                freq_to_nodes_.erase(freq);
                if (min_freq_ == freq) {
                    ++min_freq_;
                }
            }
            --size_;
        }
        min_freq_ = min(min_freq_, ++freq);
        freq_to_nodes_[freq].emplace_back(key, value, freq);
        key_to_nodeit_[key] = prev(freq_to_nodes_[freq].end());
        ++size_;
    }


