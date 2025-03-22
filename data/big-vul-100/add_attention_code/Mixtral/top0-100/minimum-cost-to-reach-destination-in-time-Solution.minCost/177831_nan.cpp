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

    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        using P = pair<int, int>;
        unordered_map<int, vector<P>> adj;
        for (const auto& edge : edges) {
            int u, v, w;
            tie(u, v, w) = make_tuple(edge[0], edge[1],edge[2]);
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        
        unordered_map<int, int> best;
        best[0] = 0;
        using T = tuple<int, int, int>;
        priority_queue<T, vector<T>, greater<T>> min_heap;
        min_heap.emplace(passingFees[0], 0, 0);
        while (!empty(min_heap)) {
            const auto [result, u, w] = min_heap.top(); min_heap.pop();
            if (w > maxTime) {  // state with best[u] < w can't be filtered, which may have less cost
                continue;
            }
            if (u == size(passingFees) - 1) {
                return result;
            }
            for (const auto& [v, nw] : adj[u]) {
                if (!best.count(v) || w + nw < best[v]) {  // from less cost to more cost, only need to check state with less time
                    best[v] = w + nw;
                    min_heap.emplace(result + passingFees[v], v, w + nw);
                }
            }
        }
        return -1;
    }

