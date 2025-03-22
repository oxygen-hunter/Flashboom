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

    int minimumVisitedCells(vector<vector<int>>& grid) {
        const int m = size(grid), n = size(grid[0]);
        vector<set<int>> bst1(m);
        vector<set<int>> bst2(n);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                bst1[i].emplace(j);
                bst2[j].emplace(i);
            }
        }
        int d = 1, i = 0, j = 0;
        vector<pair<int, int>> q = {{i, j}};
        while (!empty(q)) {
            vector<pair<int, int>> new_q;
            for (const auto& [i, j] : q) {
                if (i == m - 1 && j == n - 1) {
                    return d;
                }
                for (auto it = bst1[i].lower_bound(j + 1);
                     it != end(bst1[i]) && *it <= j + grid[i][j];
                     it = bst1[i].erase(it)) {
                    new_q.emplace_back(i, *it);
                    bst2[*it].erase(i);
                }
                for (auto it = bst2[j].lower_bound(i + 1);
                     it != end(bst2[j]) && *it <= i + grid[i][j];
                     it = bst2[j].erase(it)) {
                    new_q.emplace_back(*it, j);
                    bst1[*it].erase(j);
                }
            }
            q = move(new_q);
            ++d;
        }
        return -1;
    }

