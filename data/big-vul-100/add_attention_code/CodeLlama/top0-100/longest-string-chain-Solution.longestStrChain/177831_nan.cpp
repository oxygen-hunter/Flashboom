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


    int longestStrChain(vector<string>& words) {
        sort(words.begin(), words.end(),
             [](const string& a, const string& b) {
                 return less<int>()(a.length(), b.length());
             });
        unordered_map<string, int> dp;
        for (const auto& w : words) {
            for (int i = 0; i < w.length(); ++i) {
                auto tmp = w.substr(0, i);
                tmp += w.substr(i + 1);
                dp[w] = max(dp[w], dp[tmp] + 1);
            }
        }
        using pair_type = decltype(dp)::value_type;
        return max_element(dp.cbegin(), dp.cend(),
                           [] (const pair_type& a,
                               const pair_type& b) {
                               return a.second < b.second;
                           })->second;
    }


