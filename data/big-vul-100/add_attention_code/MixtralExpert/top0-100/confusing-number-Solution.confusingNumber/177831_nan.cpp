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


    bool confusingNumber(int N) {
        static const unordered_map<char, char> lookup = 
            {{'0', '0'}, {'1', '1'}, {'6', '9'},
             {'8', '8'}, {'9', '6'}};
 
        const auto& S = to_string(N);
        for (int i = 0; i < S.length(); ++i) {
            if (!lookup.count(S[i])) {
                return false;
            }
        }
        for (int i = 0; i < (S.length() + 1) / 2; ++i) {
            if (S[i] != lookup.at(S[S.length() - 1 - i])) {
                return true;
            }
        }
        return false;
    }


