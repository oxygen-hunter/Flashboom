walk_string(fz_context *ctx, int uni, int remove, editable_str *str)
 {
        int rune;
 
       if (str->utf8 == NULL)
                return;
 
        do
	{
		char *s = &str->utf8[str->pos];
		size_t len;
		int n = fz_chartorune(&rune, s);
		if (rune == uni)
		{
			/* Match. Skip over that one. */
			str->pos += n;
		}
		else if (uni == 32) {
			/* We don't care if we're given whitespace
			 * and it doesn't match the string. Don't
			 * skip forward. Nothing to remove. */
			break;
		}
		else if (rune == 32) {
			/* The string has a whitespace, and we
			 * don't match it; that's forgivable as
			 * PDF often misses out spaces. Remove this
			 * if we are removing stuff. */
		}
		else
		{
			/* Mismatch. No point in tracking through any more. */
			str->pos = -1;
			break;
		}
		if (remove)
		{
			len = strlen(s+n);
			memmove(s, s+n, len+1);
			str->edited = 1;
		}
	}
	while (rune != uni);
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

