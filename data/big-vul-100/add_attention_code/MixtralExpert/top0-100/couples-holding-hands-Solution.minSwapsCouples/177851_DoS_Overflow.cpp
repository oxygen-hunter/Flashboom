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


    int minSwapsCouples(vector<int>& row) {
        int N = row.size() / 2;
        vector<vector<int>> couples(N);
        for (int seat = 0; seat < row.size(); ++seat) {
            couples[row[seat] / 2].emplace_back(seat / 2);
        }
        vector<vector<int>> adj(N);
        for (const auto& couple : couples) {
            adj[couple[0]].emplace_back(couple[1]);
            adj[couple[1]].emplace_back(couple[0]);
        }
        
        int result = 0;
        for (int couch = 0; couch < N; ++couch) {
            if (adj[couch].empty()) {
                continue;
            }
            int couch1 = couch;
            int couch2 = adj[couch1].back(); adj[couch1].pop_back();
            while (couch2 != couch) {
                ++result;
                adj[couch2].erase(find(adj[couch2].begin(), adj[couch2].end(), couch1));
                couch1 = couch2;
                couch2 = adj[couch1].back(); adj[couch1].pop_back();
            }
        }
        return result;  // also equals to N - (# of cycles)
    }


