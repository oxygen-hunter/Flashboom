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

    int countQuadruples(string firstString, string secondString) {
        vector<int> lookup1(26, -1);
        for (int i = size(firstString) - 1; i >= 0; --i) {
            lookup1[firstString[i] - 'a'] = i;
        }
        vector<int> lookup2(26, -1);
        for (int i = 0; i < size(secondString); ++i) {
            lookup2[secondString[i] - 'a'] = i;
        }
        int result = 0, diff = numeric_limits<int>::max();
        for (int i = 0; i < 26; ++i) {
            if (lookup1[i] == -1 || lookup2[i] == -1) {
                continue;
            }
            if (lookup1[i] - lookup2[i] < diff) {
                diff = lookup1[i] - lookup2[i];
                result = 0;
            }                
            result += int(lookup1[i] - lookup2[i] == diff);                
        }
        return result;
    }

