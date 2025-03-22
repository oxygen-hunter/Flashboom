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


    vector<int> cheapestJump(vector<int>& A, int B) {
        vector<int> result;
        if (A.empty() || A.back() == -1) {
            return result;
        }
        const int n = A.size();
        vector<int> dp(n, numeric_limits<int>::max()), next(n, -1);
        dp[n - 1] = A[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            if (A[i] == -1) {
                continue;
            }
            for (int j = i + 1; j <= min(i + B, n - 1); ++j) {
                if (dp[j] == numeric_limits<int>::max()) {
                    continue;
                }
                if (A[i] + dp[j] < dp[i]) {
                    dp[i] = A[i] + dp[j];
                    next[i] = j;
                }
            }
        }
        if (dp[0] == numeric_limits<int>::max()) {
            return result;
        }
        int k = 0;
        while (k != -1) {
            result.emplace_back(k + 1);
            k = next[k];
        }
        return result;
    }


