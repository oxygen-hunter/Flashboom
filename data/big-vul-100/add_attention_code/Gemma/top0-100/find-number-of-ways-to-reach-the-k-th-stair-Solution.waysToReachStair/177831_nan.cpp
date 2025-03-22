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


    int waysToReachStair(int k) {
        const auto& bit_length = [](int x) {
            return (x ? std::__lg(x) : -1) + 1;
        };

        const auto& ceil_log2_x = [&](int x) {
            return bit_length(x - 1);
        };
    
        int l = ceil_log2_x(k);
        for (; (1ll << l) - k <= l + 1; ++l);
        vector<__int128> fact(l + 1, 1);
        for (int i = 0; i + 1 < size(fact); ++i) {
            fact[i + 1] = fact[i] * (i + 1);
        }
        const auto& nCr = [&](int n, int r) {
            if (!(0 <= r && r <= n)) {
                return static_cast<__int128>(0);
            }
            return fact[n] / fact[r] / fact[n - r];
        };

        int result = 0;
        for (int i = 0; i < l; ++i) {
            result += nCr(i + 1, (1 << i) - k);
        }
        return result;
    }


