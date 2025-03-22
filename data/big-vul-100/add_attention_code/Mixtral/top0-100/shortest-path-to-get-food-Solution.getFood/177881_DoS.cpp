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

    int getFood(vector<vector<char>>& grid) {
        static const vector<pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        vector<pair<int, int>> q;
        for (int r = 0; r < size(grid); ++r) {
            for (int c = 0; c < size(grid[0]); ++c) {
                if (grid[r][c] == '*') {
                    q.emplace_back(r, c);
                    break;
                }
            }
        }
        
        int result = 0;
        while (!empty(q)) {
            ++result;
            vector<pair<int, int>> new_q;
            for (const auto& [r, c] : q) {
                for (const auto& [dr, dc] : directions) {
                    int nr = r + dr, nc = c + dc;
                    if (!(0 <= nr && nr < size(grid) &&
                          0 <= nc && nc < size(grid[0]) &&
                          grid[nr][nc] != 'X')) {
                        continue;
                    }
                    if (grid[nr][nc] == '#') {
                        return result;
                    }
                    grid[nr][nc] = 'X';
                    new_q.emplace_back(nr, nc);
                }
            }
            q = move(new_q);
        }
        return -1;
    }

