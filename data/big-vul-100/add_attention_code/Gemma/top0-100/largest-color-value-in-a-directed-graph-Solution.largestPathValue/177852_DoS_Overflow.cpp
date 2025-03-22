parse_object(JsonLexContext *lex, JsonSemAction *sem)
{
	/*
	 * an object is a possibly empty sequence of object fields, separated by
	 * commas and surrounded by curly braces.
	 */
	json_struct_action ostart = sem->object_start;
    json_struct_action oend = sem->object_end;
    JsonTokenType tok;
 
    if (ostart != NULL)
        (*ostart) (sem->semstate);
 
	 * itself. Note that we increment this after we call the semantic routine
	 * for the object start and restore it before we call the routine for the
	 * object end.
	 */
	lex->lex_level++;

	/* we know this will succeeed, just clearing the token */
	lex_expect(JSON_PARSE_OBJECT_START, lex, JSON_TOKEN_OBJECT_START);

	tok = lex_peek(lex);
	switch (tok)
	{
		case JSON_TOKEN_STRING:
			parse_object_field(lex, sem);
			while (lex_accept(lex, JSON_TOKEN_COMMA, NULL))
				parse_object_field(lex, sem);
			break;
		case JSON_TOKEN_OBJECT_END:
			break;
		default:
			/* case of an invalid initial token inside the object */
			report_parse_error(JSON_PARSE_OBJECT_START, lex);
	}

	lex_expect(JSON_PARSE_OBJECT_NEXT, lex, JSON_TOKEN_OBJECT_END);

	lex->lex_level--;

	if (oend != NULL)
		(*oend) (sem->semstate);
}


    int largestPathValue(string colors, vector<vector<int>>& edges) {
        vector<vector<int>> adj(size(colors));
        vector<int> in_degree(size(colors));
        for (const auto& edge : edges) {
            adj[edge[0]].emplace_back(edge[1]);
            ++in_degree[edge[1]];
        }
        vector<int> q;
        for (int i = 0; i < size(colors); ++i) {
            if (!in_degree[i]) {
                q.emplace_back(i);
            }
        }
        vector<vector<int>> dp(size(colors), vector<int>(26));
        int result = -1, cnt = 0;
        while (!empty(q)) {
            vector<int> new_q;
            for (const auto& u : q) {
                ++cnt;
                result = max(result, ++dp[u][colors[u] - 'a']);
                for (const auto& v : adj[u]) {
                    for (int c = 0; c < 26; ++c) {
                        dp[v][c] = max(dp[v][c], dp[u][c]);
                    }
                    if (!--in_degree[v]) {
                        new_q.emplace_back(v);
                    }
                }
            }
            q = move(new_q);
        }
        return cnt == size(colors) ? result : -1;
    }


