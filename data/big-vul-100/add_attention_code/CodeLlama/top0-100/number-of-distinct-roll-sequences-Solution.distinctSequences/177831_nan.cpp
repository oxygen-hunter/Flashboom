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


    int distinctSequences(int n) {
        static const int MOD = 1e9 + 7;
        if (n == 1) {
            return 6;
        }
        vector<vector<int>> dp(6, vector<int>(6));
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                if (i != j && gcd(i + 1, j + 1) == 1) {
                    dp[i][j] = 1;
                }
            }
        }
        for (int _ = 0; _ < n - 2; ++_) {
            vector<vector<int>> new_dp(6, vector<int>(6));
            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 6; ++j) {
                    if (!dp[i][j]) {
                        continue;
                    }
                    for (int k = 0; k < 6; ++k) {
                        if (!dp[j][k]) {
                            continue;
                        }
                        if (k != i) {
                            new_dp[i][j] = (new_dp[i][j] + dp[j][k]) % MOD;
                        }
                    }
                }
            }
            dp = move(new_dp);
        }
        return accumulate(cbegin(dp), cend(dp), 0,
                          [&](int total, const auto& x) {
                              return (total + accumulate(cbegin(x), cend(x), 0,
                                                         [&](int total, int x) {
                                                             return (total + x) % MOD;
                                                         })) % MOD;
                          });
    }


