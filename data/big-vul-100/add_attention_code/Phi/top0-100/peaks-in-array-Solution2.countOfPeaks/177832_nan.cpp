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

    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
        const auto& check = [&](int i) {
            return nums[i - 1] < nums[i] && nums[i] > nums[i + 1];
        };

        BIT bit(size(nums));
        for (int i = 1; i + 1 < size(nums); ++i) {
            if (check(i)) {
                bit.add(i, +1);
            }
        }

        const auto& update = [&](int x, int d) {
            for (int i = max(x - 1, 1); i <= min(x + 1, static_cast<int>(size(nums)) - 2); ++i) {
                if (check(i)) {
                    bit.add(i, d);
                }
            }
        };

        vector<int> result;
        for (const auto& q : queries) {
            const int t = q[0], x = q[1], y = q[2];
            if (t == 1) {
                result.emplace_back(y - 1 >= x + 1 ? bit.query(y - 1) - bit.query((x + 1) - 1) : 0);
                continue;
            }
            update(x, -1);
            nums[x] = y;
            update(x, +1);
        }
        return result;
    }

