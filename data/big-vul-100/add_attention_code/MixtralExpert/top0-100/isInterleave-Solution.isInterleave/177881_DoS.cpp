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


        bool isInterleave(string s1, string s2, string s3) {
            if(s1.length() + s2.length() != s3.length()) return false;

            if(s1.length() < s2.length()) return isInterleave(s2, s1, s3);

            vector<bool> f(s2.length() + 1, true);

            for(auto j = 1; j <= s2.length(); ++j) {
                f[j] = f[j - 1] && s2[j - 1] == s3[j - 1];
            }

            for(auto i = 1; i <= s1.length(); ++i) {
                f[0] = f[0] && s1[i - 1] == s3[i - 1];
                for(auto j = 1; j <= s2.length(); ++j) {
                    f[j] = (f[j] && s1[i - 1] == s3[i + j - 1])
                        || (f[j - 1] && s2[j - 1] == s3[i + j - 1]);
                }
            }

            return f[s2.length()];
        }


