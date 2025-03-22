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

    int minOperations(vector<int>& nums) {
        static const int INF = numeric_limits<int>::max();

        const int cnt = count(cbegin(nums), cend(nums), 1);
        if (cnt) {
            return size(nums) - cnt;
        }
        int result = INF;
        for (int i = 0; i < size(nums); ++i) {
            int g = nums[i];
            for (int j = i + 1; j < size(nums); ++j) {
                g = gcd(g, nums[j]);
                if (g == 1) {
                    result = min(result, j - i);
                    break;
                }
            }
        }
        return result != INF ? result + (size(nums) - 1) : -1;
    }

