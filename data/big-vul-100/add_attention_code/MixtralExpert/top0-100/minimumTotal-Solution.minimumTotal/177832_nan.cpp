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


        int minimumTotal(vector<vector<int> > &triangle) {
            const int N = triangle.size();
            vector<int> f(N, INT_MAX);
            int ans = INT_MAX;

            f[0] = triangle[0][0];
            for(int i = 1; i < N; ++i) {
                for(int j = i; j > 0; --j) {
                    f[j] = min(f[j], f[j - 1]) + triangle[i][j];
                }
                f[0] += triangle[i][0];
            }

            for(int i = 0; i < N; ++i) {
                ans = min(ans, f[i]);
            }

            return ans;
        }


