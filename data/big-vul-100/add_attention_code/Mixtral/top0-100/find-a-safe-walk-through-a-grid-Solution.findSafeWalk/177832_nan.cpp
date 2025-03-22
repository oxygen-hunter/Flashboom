walk_string(fz_context *ctx, int uni, int remove, editable_str *str)
 {
        int rune;
 
       if (str->utf8 == NULL)
                return;
 
        do
	{
		char *s = &str->utf8[str->pos];
		size_t len;
		int n = fz_chartorune(&rune, s);
		if (rune == uni)
		{
			/* Match. Skip over that one. */
			str->pos += n;
		}
		else if (uni == 32) {
			/* We don't care if we're given whitespace
			 * and it doesn't match the string. Don't
			 * skip forward. Nothing to remove. */
			break;
		}
		else if (rune == 32) {
			/* The string has a whitespace, and we
			 * don't match it; that's forgivable as
			 * PDF often misses out spaces. Remove this
			 * if we are removing stuff. */
		}
		else
		{
			/* Mismatch. No point in tracking through any more. */
			str->pos = -1;
			break;
		}
		if (remove)
		{
			len = strlen(s+n);
			memmove(s, s+n, len+1);
			str->edited = 1;
		}
	}
	while (rune != uni);
}

    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        static const vector<pair<int, int>> directions = {{0, 1}, {0, -1},
                                                          {1, 0}, {-1, 0}};
        const pair<int, int> b = {0, 0}, t = {size(grid) - 1, size(grid[0]) - 1};
        if (!(0 + grid[0][0] < health)) {
            return false;
        }
        deque<pair<pair<int, int>, int>> dq = {{b, grid[0][0]}};
        unordered_set<int> lookup;
        while (!empty(dq)) {
            const auto [b, d] = dq.front(); dq.pop_front();
            if (b == t) {
                return true;
            }
            if (lookup.count(b.first * size(grid[0]) + b.second)) {
                continue;
            }
            lookup.emplace(b.first * size(grid[0]) + b.second);
            for (const auto& [dr, dc] : directions) {
                const auto& nb = make_pair(b.first + dr, b.second + dc);
                if (!(0 <= nb.first && nb.first < size(grid) &&
                      0 <= nb.second && nb.second < size(grid[0]) &&
                      !lookup.count(nb.first * size(grid[0]) + nb.second))) {
                    continue;
                }
                if (!grid[nb.first][nb.second]) {
                    dq.emplace_front(nb, d);
                } else if (d + 1 < health) {
                    dq.emplace_back(nb, d + 1);
                }
            }
        }
        return false;
    }

