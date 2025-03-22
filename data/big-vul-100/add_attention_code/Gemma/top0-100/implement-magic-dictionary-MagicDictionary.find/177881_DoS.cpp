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


    bool find(const string& word, TrieNode *curr, int i, bool mistakeAllowed) {
        if (i == word.length()) {
            return curr->isString && !mistakeAllowed; 
        }

        if (!curr->leaves.count(word[i])) {
            return mistakeAllowed ?
                       any_of(curr->leaves.begin(), curr->leaves.end(),
                              [&](const pair<char, TrieNode *>& kvp) { 
                                  return find(word, kvp.second, i + 1, false);
                               }) :
                       false;
        }
                    
        if (mistakeAllowed) {
            return find(word, curr->leaves[word[i]], i + 1, true) ||
                   any_of(curr->leaves.begin(), curr->leaves.end(),
                          [&](const pair<char, TrieNode *>& kvp) { 
                              return kvp.first != word[i] && find(word, kvp.second, i + 1, false);
                          });
        }
        return find(word, curr->leaves[word[i]], i + 1, false);
    }


