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

    vector<vector<int>> seePeople(vector<vector<int>>& heights) {
        vector<vector<int>> result(size(heights), vector<int>(size(heights[0])));
        const auto& count = [](const auto& height, int i, vector<int> *stk, const auto& increase) {
            while (!empty(*stk) && height(stk->back()) < height(i)) {
                increase(stk->back()); stk->pop_back();
            }
            if (!empty(*stk)) {
                increase(stk->back());
            }
            if (!empty(*stk) && height(stk->back()) == height(i)) {
                stk->pop_back();
            }
            stk->emplace_back(i);
        };

        for (int i = 0; i < size(heights); ++i) {
            const auto& height = [&](int x) {
                return heights[i][x];
            };
            const auto& increase = [&](int x) {
                ++result[i][x];
            };
            vector<int> stk;
            for (int j = 0; j < size(heights[0]); ++j) {
                count(height, j, &stk, increase);
            }
        }
        for (int j = 0; j < size(heights[0]); ++j) {
            const auto& height = [&](int x) {
                return heights[x][j];
            };
            const auto& increase = [&](int x) {
                ++result[x][j];
            };
            vector<int> stk;
            for (int i = 0; i < size(heights); ++i) {
                count(height, i, &stk, increase);
            }
        }
        return result;
    }

