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


    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        static const int DISTANCE = 2;

        vector<unordered_set<int>> adj(size(coins));
        for (const auto& e : edges) {
            adj[e[0]].emplace(e[1]);
            adj[e[1]].emplace(e[0]);
        }
        int n = size(coins);
        for (int i = 0; i < size(coins); ++i) {
            int u = i;
            while (size(adj[u]) == 1 && !coins[u]) {
                const int v = *cbegin(adj[u]);
                adj[u].erase(v);
                adj[v].erase(u);
                --n;
                u = v;
            }
        }
        vector<int> q;
        for (int u = 0; u < size(coins); ++u) {
            if (size(adj[u]) == 1) {
                q.emplace_back(u);
            }
        }
        for (int _ = 0; _ < DISTANCE; ++_) {
            vector<int> new_q;
            for (const auto& u : q) {
                if (empty(adj[u])) {
                    assert(n == 1);
                    break;
                }
                const int v = *cbegin(adj[u]);
                adj[u].erase(v);
                adj[v].erase(u);
                --n;
                if (size(adj[v]) == 1) {
                    new_q.emplace_back(v);
                }
            }
            q = move(new_q);
        }
        return (n - 1) * 2;
    }


