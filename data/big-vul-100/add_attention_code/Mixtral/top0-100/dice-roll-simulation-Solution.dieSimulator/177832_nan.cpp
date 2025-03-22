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

    int dieSimulator(int n, vector<int>& rollMax) {
        static const int MOD = 1e9 + 7;
        vector<vector<int>> dp;
        for (int i = 0; i < 6; ++i) {
            dp.emplace_back(rollMax[i]);
            dp[i][0] = 1;  // 0-indexed
        }
        while (--n) {
            vector<vector<int>> new_dp;
            for (int i = 0; i < 6; ++i) {
                new_dp.emplace_back(rollMax[i]);  
            }
            for (int i = 0; i < 6; ++i) {
                for (int k = 0; k < rollMax[i]; ++k) {
                    for (int j = 0; j < 6; ++j) {
                        if (i == j) {
                            if (k < rollMax[i] - 1) {  // 0-indexed
                                new_dp[j][k + 1] = (new_dp[j][k + 1] + dp[i][k]) % MOD;
                            }
                        } else {
                            new_dp[j][0] = (new_dp[j][0] + dp[i][k]) % MOD;
                        }
                    }
                }
            }
            dp = move(new_dp);
        }
        uint64_t result = 0;
        for (const auto& row : dp) {
            const auto& total =
                accumulate(row.cbegin(), row.cend(),
                           0ull,
                           [&](const auto& a, const auto& b) {
                               return (a + b) % MOD;
                           });
            result = (result + total) % MOD;
        }
        return result;
    }

