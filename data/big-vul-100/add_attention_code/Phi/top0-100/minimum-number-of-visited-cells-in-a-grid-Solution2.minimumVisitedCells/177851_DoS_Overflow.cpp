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

