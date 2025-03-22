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


    vector<int> gridIllumination(int N, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
        unordered_set<int64_t> lookup;
        unordered_map<int, int> row, col, diag, anti;
        for (const auto& lamp : lamps) {
            int r, c;
            tie(r, c) = make_pair(lamp[0], lamp[1]);
            if (!lookup.emplace(static_cast<int64_t>(r) * N + c).second) {
                continue;
            }
            ++row[r];
            ++col[c];
            ++diag[r - c];
            ++anti[r + c];
        }
        
        vector<int> result;
        for (const auto& query : queries) {
            int r, c;
            tie(r, c) = make_pair(query[0], query[1]);
            if (!(row[r] || col[c] || diag[r - c] || anti[r + c])) {
                result.emplace_back(0);
                continue;
            }
            result.emplace_back(1);
            for (int nr = max(r - 1, 0); nr <= min(r + 1, N - 1); ++nr) {
                for (int nc = max(c - 1, 0); nc <= min(c + 1, N - 1); ++nc) {
                    if (!lookup.erase(static_cast<int64_t>(nr) * N + nc)) {
                        continue;
                    }
                    --row[nr];
                    --col[nc];
                    --diag[nr - nc];
                    --anti[nr + nc];
                }
            }
        }
        return result;
    }


