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


    vector<vector<int>> findRLEArray(vector<vector<int>>& encoded1, vector<vector<int>>& encoded2) {
        vector<vector<int>> result;
        for (int i = 0, j = 0, remain1 = 0, remain2 = 0;
             (remain1 || i < size(encoded1)) && (remain2 || j < size(encoded2));) {
            if (!remain1) {
                remain1 = encoded1[i++][1];
            }
            if (!remain2) {
                remain2 = encoded2[j++][1];
            }
            int cnt = min(remain1, remain2);
            remain1 -= cnt;
            remain2 -= cnt;
            if (!empty(result) && result.back()[0] == encoded1[i - 1][0] * encoded2[j - 1][0]) {
                result.back()[1] += cnt;
            } else {
                result.push_back({encoded1[i - 1][0] * encoded2[j - 1][0], cnt});
            }
        }
        return result;
    }


