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


    long long minimumTotalCost(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> cnt;
        int64_t result = 0;
        for (int i = 0; i < size(nums1); ++i) {
            if (nums1[i] != nums2[i]) {
                continue;
            }
            ++cnt[nums1[i]];
            result += i;
        }
        if (empty(cnt)) {
            return 0;
        }
        const int majority = max_element(cbegin(cnt), cend(cnt),
                                         [](const auto& a, const auto& b) {
                                                return a.second < b.second;
                                         })->first;
        int remain = cnt[majority] - (accumulate(cbegin(cnt), cend(cnt), 0,
                                                 [](const auto& total, const auto& x) {
                                                     return total + x.second;
                                                 }) - cnt[majority]);
        if (remain <= 0) {
            return result;
        }
        for (int i = 0; i < size(nums1); ++i) {
            if (nums1[i] == nums2[i] || nums1[i] == majority || nums2[i] == majority) {
                continue;
            }
            result += i;
            if (--remain == 0) {
                return result;
            }
        }
        return -1;
    }


