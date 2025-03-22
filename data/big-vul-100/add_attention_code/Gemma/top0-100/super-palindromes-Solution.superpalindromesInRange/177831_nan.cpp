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


    int superpalindromesInRange(string L, string R) {
        const auto K = static_cast<int>(pow(10, (R.length() + 1) * 0.25));
        const int64_t l = stol(L), r = stol(R);
        int result = 0;

        // count odd length
        for (int k = 0; k < K; ++k) {
            const string s = to_string(k), rev_s(s.rbegin(), s.rend());
            int64_t v = stol(s + rev_s.substr(1));
            v *= v;
            if (v > r) {
                break;
            }
            if (v >= l && is_palindrome(v)) {
                ++result;
            }
        }

        // count even length
        for (int k = 0; k < K; ++k) {
            const string s = to_string(k), rev_s(s.rbegin(), s.rend());
            int64_t v = stol(s + rev_s);
            v *= v;
            if (v > r) {
                break;
            }
            if (v >= l && is_palindrome(v)) {
                ++result;
            }
        }

        return result;
    }


