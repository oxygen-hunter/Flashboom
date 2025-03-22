parse_array(JsonLexContext *lex, JsonSemAction *sem)
{
	/*
	 * an array is a possibly empty sequence of array elements, separated by
	 * commas and surrounded by square brackets.
	 */
	json_struct_action astart = sem->array_start;
	json_struct_action aend = sem->array_end;
    json_struct_action astart = sem->array_start;
    json_struct_action aend = sem->array_end;
 
    if (astart != NULL)
        (*astart) (sem->semstate);
 
	 * array end.
	 */
	lex->lex_level++;

	lex_expect(JSON_PARSE_ARRAY_START, lex, JSON_TOKEN_ARRAY_START);
	if (lex_peek(lex) != JSON_TOKEN_ARRAY_END)
	{

		parse_array_element(lex, sem);

		while (lex_accept(lex, JSON_TOKEN_COMMA, NULL))
			parse_array_element(lex, sem);
	}

	lex_expect(JSON_PARSE_ARRAY_NEXT, lex, JSON_TOKEN_ARRAY_END);

	lex->lex_level--;

	if (aend != NULL)
		(*aend) (sem->semstate);
}

    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        static const int MOD = 1e9 + 7;
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& e : edges) {
            int u = e[0] - 1, v = e[1] - 1, w = e[2];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        vector<int> dist(n, numeric_limits<int>::max()), dp(n);
        dist[n - 1] = 0;
        dp[n - 1] = 1;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
        min_heap.emplace(0, n - 1);
        while (!empty(min_heap)) {
            const auto [w, u] = min_heap.top(); min_heap.pop();
            if (w > dist[u]) {
                continue;
            }
            for (const auto& [v, d] : adj[u]) {
                if (w + d < dist[v]) {
                    dist[v] = w + d;
                    min_heap.emplace(dist[v], v);
                } else if (w > dist[v]) {
                    dp[u] = (dp[u] + dp[v]) % MOD;
                }
            }
            if (u == 0) {  // early return
                break;
            }
        }
        return dp[0];
    }

