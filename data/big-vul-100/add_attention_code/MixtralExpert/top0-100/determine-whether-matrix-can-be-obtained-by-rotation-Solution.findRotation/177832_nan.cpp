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


    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        vector<function<bool (int, int)>> checks = {
            [&mat, &target](int i, int j) { return mat[i][j] == target[i][j]; },
            [&mat, &target](int i, int j) { return mat[i][j] == target[j][size(mat) - 1 - i]; },
            [&mat, &target](int i, int j) { return mat[i][j] == target[size(mat) - 1 - i][size(mat[0]) - 1 - j]; },
            [&mat, &target](int i, int j) { return mat[i][j] == target[size(mat[0]) - 1 - j][i]; },
        };
        const auto& traverse = [&mat, &target](const auto& check) {
            for (int i = 0; i < size(mat); ++i) {
                for (int j = 0; j < size(mat[0]); ++j) {
                    if (!check(i, j)) {
                        return false;
                    }
                }
            }
            return true;
        };
        for (const auto& check : checks) {
            if (traverse(check)) {
                return true;
            }
        }
        return false;
    }


