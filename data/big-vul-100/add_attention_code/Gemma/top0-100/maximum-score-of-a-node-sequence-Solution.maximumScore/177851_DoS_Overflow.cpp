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


    int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
        using PII = pair<int, int>;
        using Heap = vector<PII>;
        const auto& find_top3 = [&scores](const auto& x, Heap *top3) {            
            top3->emplace_back(scores[x], x); push_heap(begin(*top3), end(*top3), greater<PII>());
            if (size(*top3) > 3) {
                pop_heap(begin(*top3), end(*top3), greater<PII>()); top3->pop_back();
            }
        };
        vector<Heap> top3(size(scores));
        for (const auto& e : edges) {
            find_top3(e[1], &top3[e[0]]);
            find_top3(e[0], &top3[e[1]]);
        }
        int result = -1;
        for (const auto& e : edges) {
            const int a = e[0], b = e[1];
            for (const auto& [_, c] : top3[a]) {
                if (c == b) {
                    continue;
                }
                for (const auto& [_, d] : top3[b]) {
                    if (d == a || d == c) {
                        continue;
                    }
                    result = max(result, scores[a] + scores[b] + scores[c] + scores[d]);
                }
            }
        }
        return result;
    }


