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


    int minimumFinishTime(vector<vector<int>>& tires, int changeTime, int numLaps) {
        static const int INF = numeric_limits<int>::max();

        const auto& ceil_log2 = [](const auto& x) {
            return std::__lg(x - 1) + 1;
        };
        vector<int64_t> dp(ceil_log2(changeTime + 1), INF);  // dp[i]: min time to complete i+1 laps without changing a tire
        for (int i = 0; i < size(tires); ++i) {
            const int f = tires[i][0], r = tires[i][1];
            for (int64_t curr = f, total = f, cnt = 0;
                 curr < changeTime + f;
                 curr *= r, total += curr, ++cnt) {  // at worst (f, r) = (1, 2) => 2^(cnt-1) < changeTime+1 => cnt < ceil(log2(changeTime+1))
                dp[cnt] = min(dp[cnt], total);
            }
        }
        vector<int64_t> dp2(numLaps, INF);  // dp2[i]: min time to complete i+1 laps with changing zero or more tires
        for (int i = 0; i < numLaps; ++i) {
            for (int j = 0; j < min(i + 1, static_cast<int>(size(dp))); ++j) {
                dp2[i] = min(dp2[i], (i - j - 1 >= 0 ? dp2[i - j - 1] + changeTime : 0) + dp[j]);
            }
        }
        return dp2.back();
    }


