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

    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        const auto& ceil_divide = [](const auto& a, const auto& b) {
            return (a + b - 1) / 2;
        };

        const auto& tree_diameter = [](const auto& edges) {
            vector<vector<int>> adj(size(edges) + 1);
            for (const auto& e : edges) {
                adj[e[0]].emplace_back(e[1]);
                adj[e[1]].emplace_back(e[0]);
            }
            int result = 0;
            const auto& bfs = [&](int root) {
                int d = -1, new_root = -1;
                vector<bool> lookup(size(adj));
                lookup[root] = true;
                vector<int> q = {root};
                while (!empty(q)) {
                    ++d;
                    new_root = q[0];
                    vector<int> new_q;
                    for (const auto& u : q) {
                        for (const auto& v : adj[u]) {
                            if (lookup[v]) {
                                continue;
                            }
                            lookup[v] = true;
                            new_q.emplace_back(v);
                        }
                    }
                    q = move(new_q);
                }
                return pair(d, new_root);
            };

            const auto& [_, root] = bfs(0);
            const auto& [d, __] = bfs(root);
            return d;
        };

        const int d1 = tree_diameter(edges1);
        const int d2 = tree_diameter(edges2);
        return max({ceil_divide(d1, 2) + 1 + ceil_divide(d2, 2), d1, d2});
    }

