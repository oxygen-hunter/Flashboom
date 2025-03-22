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


    int findInteger(int k, int digit1, int digit2) {
        static const int MAX_NUM_OF_DIGITS = 10;

        if (digit1 < digit2) {
            swap(digit1, digit2);
        }
        for (int l = 1, total = 2; l <= MAX_NUM_OF_DIGITS; ++l, total <<= 1) {
            for (int mask = 0; mask < total; ++mask) {
                int64_t curr = 0;
                for (int bit = total >> 1; bit; bit >>= 1) {
                    curr = curr * 10 + ((mask & bit) ? digit1 : digit2);
                }
                if (k < curr && curr <= numeric_limits<int>::max() && curr % k == 0) {
                    return curr;
                }
            }
        }
        return -1; 
    }


