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


    int maxDistance(vector<vector<int>>& grid) {
        static const vector<pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        queue<pair<int, int>> q;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j]) {
                    q.emplace(i, j);
                }
            }
        }
        if (q.size() == grid.size() * grid[0].size()) {
            return -1;
        }
        int level = -1;
        while (!q.empty()) {
            queue<pair<int, int>> next_q;
            while (!q.empty()) {
                const auto [x, y] = q.front(); q.pop();
                for (const auto& [dx, dy] : directions) {
                    const auto& nx = x + dx;
                    const auto& ny = y + dy;
                    if (!(0 <= nx && nx < grid.size() && 
                          0 <= ny && ny < grid[0].size() && 
                          grid[nx][ny] == 0)) {
                        continue;
                    }
                    next_q.emplace(nx, ny);
                    grid[nx][ny] = 1;
                }
            }
            q = move(next_q);
            ++level;
        }
        return level;
    }


