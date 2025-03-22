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


    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        static const int MOD = 1e9 + 7;
        uint64_t result = 0, s_sum = 0;
        vector<pair<int, int>> engineers;
        for (int i = 0; i < speed.size(); ++i) {
            engineers.emplace_back(efficiency[i], speed[i]);
        }
        sort(engineers.begin(), engineers.end(), greater<pair<int, int>>());
        priority_queue<int, vector<int>, greater<int>> min_heap;
        for (const auto& [e, s] : engineers) {
            s_sum += s;
            min_heap.emplace(s);
            if (min_heap.size() > k) {
                s_sum -= min_heap.top(); min_heap.pop();
            }
            result = max(result, s_sum * e);
        }
        return result % MOD;
    }


