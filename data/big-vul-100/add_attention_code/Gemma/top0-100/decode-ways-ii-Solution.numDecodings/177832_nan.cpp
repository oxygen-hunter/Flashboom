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


    int numDecodings(string s) {
        static const int M = 1000000007;
        static const int W = 3;
        vector<long long> dp(W);
        dp[0] = 1;
        dp[1] = s[0] == '*' ? 9 : (s[0] != '0' ? dp[0] : 0);
        for (int i = 1; i < s.length(); ++i) {
            if (s[i] == '*') {
                dp[(i + 1) % W] = 9 * dp[i % W];
                if (s[i - 1] == '1') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + 9 * dp[(i - 1) % W]) % M;
                } else if (s[i - 1] == '2') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + 6 * dp[(i - 1) % W]) % M;
                } else if (s[i - 1] == '*') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + 15 * dp[(i - 1) % W]) % M;
                }
            } else {
                dp[(i + 1) % W] = s[i] != '0' ? dp[i % W] : 0;
                if (s[i - 1] == '1') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + dp[(i - 1) % W]) % M;
                } else if (s[i - 1] == '2' && s[i] <= '6') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + dp[(i - 1) % W]) % M;
                } else if (s[i - 1] == '*') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + (s[i] <= '6' ? 2 : 1) * dp[(i - 1) % W]) % M;
                }
            }
        }
        return static_cast<int>(dp[s.length() % W]);
    }


