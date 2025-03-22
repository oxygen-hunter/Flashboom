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

    int totalStrength(vector<int>& strength) {
        static const int MOD = 1e9 + 7;
        const auto& add = [&](const int64_t a, const int64_t b) {
            return (a + b) % MOD;
        };
        const auto& sub = [&](const int64_t a, const int64_t b) {
            return (a - b + MOD) % MOD;
        };
        const auto& mult = [&](const int64_t a, const int64_t b) {
            return (a * b) % MOD;
        };
        vector<int64_t> prefix(size(strength) + 1), prefix2(size(strength) + 1);
        for (int i = 0; i < size(strength); ++i) {
            prefix[i + 1] = add(prefix[i], strength[i]);
            prefix2[i + 1] = add(prefix2[i], strength[i] * static_cast<int64_t>(i + 1));
        }
        vector<int64_t> suffix(size(strength) + 1), suffix2(size(strength) + 1);
        for (int i = size(strength) - 1; i >= 0; --i) {
            suffix[i] = add(suffix[i + 1], strength[i]);
            suffix2[i] = add(suffix2[i + 1], strength[i] * (size(strength) - i));
        }
        vector<int> stk = {-1};
        int result = 0;
        for (int i = 0; i <= size(strength); ++i) {
            while (stk.back() != -1 && (i == size(strength) || strength[stk.back()] >= strength[i])) {
                const int x = stk[size(stk) - 2] + 1;
                const int y = stk.back(); stk.pop_back();
                const int z = i - 1;
                // assert(all(strength[j] >= strength[y] for j in xrange(x, y+1)))
                // assert(all(strength[j] > strength[y] for j in xrange(y+1, z+1)))
                const int64_t left = mult(z - y + 1, sub(sub(prefix2[y + 1], prefix2[x]), mult(x, sub(prefix[y + 1], prefix[x]))));
                const int64_t right = mult(y - x + 1, sub(sub(suffix2[y + 1], suffix2[z + 1]), mult(size(strength) - (z + 1), sub(suffix[y + 1], suffix[z + 1]))));
                result = add(result, mult(strength[y], add(left, right)));
            }
            stk.emplace_back(i);
        }
        return result;
    }

