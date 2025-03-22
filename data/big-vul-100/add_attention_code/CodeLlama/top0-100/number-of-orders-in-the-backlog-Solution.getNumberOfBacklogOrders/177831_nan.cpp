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


    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        static const int MOD = 1e9 + 7;

        priority_queue<vector<int>> buy;  // max_heap
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> sell;  // min_heap
        for (const auto& o : orders) {
            if (o[2] == 0) {
                buy.emplace(o);
            } else {
                sell.emplace(o);
            }
            while (!empty(buy) && !empty(sell) && sell.top()[0] <= buy.top()[0]) {
                int k = min(buy.top()[1], sell.top()[1]);
                auto tmp = buy.top(); buy.pop();
                tmp[1] -= k;
                if (tmp[1]) {
                    buy.emplace(tmp);
                }
                tmp = sell.top(); sell.pop();
                tmp[1] -= k;
                if (tmp[1]) {
                    sell.emplace(tmp);
                }
            }

        }
        int result = 0;
        while (!empty(buy)) {
            result = (result + buy.top()[1]) % MOD; buy.pop();
        }
        while (!empty(sell)) {
            result = (result + sell.top()[1]) % MOD; sell.pop();
        }
        return result;
    }


