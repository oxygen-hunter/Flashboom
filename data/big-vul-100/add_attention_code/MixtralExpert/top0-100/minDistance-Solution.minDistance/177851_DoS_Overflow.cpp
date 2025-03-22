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


        int minDistance(string word1, string word2) {
            const size_t m = word1.size();
            const size_t n = word2.size();

            if(m < n)
                return minDistance(word2, word1);

            vector<size_t> f(n + 1, 0);
            size_t upper_left;

            for(size_t i = 0; i < n + 1; ++i)
                f[i] = i;

            for(size_t i = 1; i < m + 1; ++i) {
                upper_left = f[0];
                f[0] = i;
                for(size_t j = 1; j < n + 1; ++j) {
                    size_t upper = f[j];
                    if(word1[i - 1] == word2[j - 1])
                        f[j] = upper_left;
                    else {
                        f[j] = 1 + min(upper_left, min(f[j - 1], f[j]));
                    }
                    upper_left = upper;
                }
            }

            return f[n];
        }


