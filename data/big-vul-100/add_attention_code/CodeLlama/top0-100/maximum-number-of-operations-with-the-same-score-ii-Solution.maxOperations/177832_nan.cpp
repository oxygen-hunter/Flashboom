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


    int maxOperations(vector<int>& nums) {
        const function<int (int, int, int, vector<vector<int>>&)> memoization = [&](int left, int right, int target, vector<vector<int>>& lookup) {
            if (!(right - left + 1 >= 2)) {
                return 0;
            }
            if (lookup[left][right] == -1) {
                lookup[left][right] = max({nums[left] + nums[left + 1]   == target ? 1 + memoization(left + 2, right - 0, target, lookup) : 0,
                                           nums[left] + nums[right]      == target ? 1 + memoization(left + 1, right - 1, target, lookup) : 0,
                                           nums[right - 1] + nums[right] == target ? 1 + memoization(left + 0, right - 2, target, lookup) : 0});
            }
            return lookup[left][right];
        };

        int result = 0;
        for (const auto& target : unordered_set<int>{nums[0] + nums[1], nums[0] + nums[size(nums) - 1], nums[size(nums) - 2] + nums[size(nums) - 1]}) {
            vector<vector<int>> lookup(size(nums), vector<int>(size(nums), -1));
            result = max(result, memoization(0, size(nums) - 1, target, lookup));
        }
        return result;
    }


