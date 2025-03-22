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

    int minMoves(vector<int>& nums, int k) {
        vector<int> idxs;
        for (int i = 0; i < size(nums); ++i) {
            if (nums[i]) {
                idxs.emplace_back(i);
            }
        }
        vector<uint64_t> prefix(size(idxs) + 1);
        for (int i = 0; i < size(idxs); ++i) {
            prefix[i + 1] = prefix[i] + idxs[i];
        }
        const auto& score = [&prefix](int i, int j) {
                                return prefix[j + 1] - prefix[i];
                            };
        uint64_t result = numeric_limits<uint64_t>::max();
        for (int i = 0; i < size(idxs) - k + 1; ++i) {
            result = min(result, -score(i, i + k / 2 - 1) + score(i + (k + 1) / 2, i + k - 1));  // take each i+k//2 as median, find min dist to median
        }
        result -= (k / 2) * ((k + 1) / 2);  // rollback extra moves to the expected positions
        return result;
    }

