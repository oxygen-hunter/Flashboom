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

