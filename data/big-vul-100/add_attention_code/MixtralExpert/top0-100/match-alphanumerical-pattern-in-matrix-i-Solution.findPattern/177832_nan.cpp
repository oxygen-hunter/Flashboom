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


    vector<int> findPattern(vector<vector<int>>& board, vector<string>& pattern) {
        const auto& check = [&](int i, int j) {
            vector<int> lookup(26, -1);
            vector<bool> lookup2(10);
            for (int r = 0; r < size(pattern); ++r) {
                for (int c = 0; c < size(pattern[0]); ++c) {
                    const int y = board[i + r][j + c];
                    if (isdigit(pattern[r][c])) {
                        if (pattern[r][c] - '0' != y) {
                            return false;
                        }
                        continue;
                    }
                    const int x = pattern[r][c] - 'a';
                    if (lookup[x] == -1) {
                        if (lookup2[y]) {
                            return false;
                        }
                        lookup2[y] = true;
                        lookup[x] = y;
                        continue;
                    }
                    if (lookup[x] != y) {
                        return false;
                    }
                }
            }
            return true;
        };
    
        for (int i = 0; i + size(pattern) - 1 < size(board); ++i) {
            for (int j = 0; j + size(pattern[0]) - 1 < size(board[0]); ++j) {
                if (check(i, j)) {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }


