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


    string shortestBeautifulSubstring(string s, int k) {
        const auto& check = [&](int l1, int r1, int l2, int r2) {
            const int c1 = r1 - l1 + 1, c2 = r2 -l2 + 1;
            if (c1 > c2) {
                return false;
            }
            if (c1 < c2) {
                return true;
            }
            for (int i = 0; i < c1; ++i) {
                if (s[l1 + i] != s[l2 + i]) {
                    return s[l1 + i] < s[l2 + i];
                }
            }
            return false;
        };
        
        vector<int> result = {};
        for (int right = 0, left = 0, curr = 0; right < size(s); ++right) {
            curr += static_cast<int>(s[right] == '1');
            while (curr == k + 1) {
                curr -= static_cast<int>(s[left++] == '1');
            }
            while (left < size(s) && s[left] == '0') {
                ++left;
            }
            if (curr == k) {
                if (empty(result) || check(left, right, result[0], result[1])) {
                    result = {left, right};
                }
            }
        }
        return !empty(result) ? s.substr(result[0], result[1] - result[0] + 1) : "";
    }


