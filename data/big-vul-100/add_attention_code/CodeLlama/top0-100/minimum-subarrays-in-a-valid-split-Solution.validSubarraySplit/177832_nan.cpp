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


    int validSubarraySplit(vector<int>& nums) {
        static const int INF = numeric_limits<int>::max();

        vector<int> dp(size(nums) + 1, INF);  // dp[i]: min number of subarrays in nums[:i]
        dp[0] = 0;
        for (int i = 1; i <= size(nums); ++i) {
            for (int j = 0; j < i; ++j) {
                if (gcd(nums[j], nums[i - 1]) != 1) {
                    if (dp[j] != INF) {
                        dp[i] = min(dp[i], dp[j] + 1);
                    }
                }
            }
        }
        return dp.back() != INF ? dp.back() : -1;
    }


