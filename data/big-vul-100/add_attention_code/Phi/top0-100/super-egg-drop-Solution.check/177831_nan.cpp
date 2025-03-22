mcid_char_imp(fz_context *ctx, pdf_filter_processor *p, tag_record *tr, int uni, int remove)
{
	if (tr->mcid_obj == NULL)
		/* No object, or already deleted */
		return;

	if (remove)
	{
		/* Remove the expanded abbreviation, if there is one. */
		pdf_dict_del(ctx, tr->mcid_obj, PDF_NAME(E));
                /* Remove the structure title, if there is one. */
                pdf_dict_del(ctx, tr->mcid_obj, PDF_NAME(T));
        }
        /* Edit the Alt string */
        walk_string(ctx, uni, remove, &tr->alt);
        /* Edit the ActualText string */
        walk_string(ctx, uni, remove, &tr->actualtext);
        /* If we're removing a character, and either of the strings
         * haven't matched up to what we were expecting, then just
         * delete the whole string. */
	else if (tr->alt.pos >= 0 || tr->actualtext.pos >= 0)
	{
		/* The strings are making sense so far */
		remove = 0;
                /* The strings are making sense so far */
                remove = 0;
        }
        if (remove)
        {
                /* Anything else we have to err on the side of caution and
		if (tr->alt.pos == -1)
			pdf_dict_del(ctx, tr->mcid_obj, PDF_NAME(Alt));
		pdf_drop_obj(ctx, tr->mcid_obj);
		tr->mcid_obj = NULL;
		fz_free(ctx, tr->alt.utf8);
		tr->alt.utf8 = NULL;
		fz_free(ctx, tr->actualtext.utf8);
		tr->actualtext.utf8 = NULL;
	}
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

