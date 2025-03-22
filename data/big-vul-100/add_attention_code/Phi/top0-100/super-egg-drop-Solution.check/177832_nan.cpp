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

    bool check(int n, int K, int N) {
        // let f(n, K) be the max number of floors could be solved by n moves and K eggs,
        // we want to do binary search to find min of n, s.t. f(n, K) >= N,
        // if we use one move to drop egg with X floors
        // 1. if it breaks, we can search new X in the range [X+1, X+f(n-1, K-1)]
        // 2. if it doesn't break, we can search new X in the range [X-f(n-1, K), X-1]
        // => f(n, K) = (X+f(n-1, K-1))-(X-f(n-1, K))+1 = f(n-1, K-1)+f(n-1, K)+1
        // => (1) f(n, K)   = f(n-1, K)  +1+f(n-1, K-1)
        //    (2) f(n, K-1) = f(n-1, K-1)+1+f(n-1, K-2)
        // let g(n, K) = f(n, K)-f(n, K-1), and we subtract (1) by (2)
        // => g(n, K) = g(n-1, K)+g(n-1, K-1), obviously, it is binomial coefficient
	    // => C(n, K) = g(n, K) = f(n, K)-f(n, K-1),
        //    which also implies if we have one more egg with n moves and x-1 egges, we can have more C(n, x) floors solvable
        // => f(n, K) = C(n, K)+f(n, K-1) = C(n, K) + C(n, K-1) + ... + C(n, 1) + f(n, 0) = sum(C(n, k) for k in [1, K])
        // => all we have to do is to check sum(C(n, k) for k in [1, K]) >= N,
        //    if true, there must exist a 1-to-1 mapping from each F in [1, N] to each sucess and failure sequence of every C(n, k) combinations for k in [1, K]
        int total = 0, c = 1;
        for (int k = 1; k <= K; ++k) {
            c *= n - k + 1;
            c /= k;
            total += c;
            if (total >= N) {
                return true;
            }
        }
        return false;
    }

