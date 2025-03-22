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


        bool isInterleave(string s1, string s2, string s3) {
            if(s1.length() + s2.length() != s3.length()) return false;

            if(s1.length() < s2.length()) return isInterleave(s2, s1, s3);

            vector<bool> f(s2.length() + 1, true);

            for(auto j = 1; j <= s2.length(); ++j) {
                f[j] = f[j - 1] && s2[j - 1] == s3[j - 1];
            }

            for(auto i = 1; i <= s1.length(); ++i) {
                f[0] = f[0] && s1[i - 1] == s3[i - 1];
                for(auto j = 1; j <= s2.length(); ++j) {
                    f[j] = (f[j] && s1[i - 1] == s3[i + j - 1])
                        || (f[j - 1] && s2[j - 1] == s3[i + j - 1]);
                }
            }

            return f[s2.length()];
        }


