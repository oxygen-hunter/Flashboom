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

