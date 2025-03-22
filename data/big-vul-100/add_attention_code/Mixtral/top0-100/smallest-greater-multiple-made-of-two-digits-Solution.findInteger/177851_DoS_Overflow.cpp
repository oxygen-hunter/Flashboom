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

    int findInteger(int k, int digit1, int digit2) {
        static const int MAX_NUM_OF_DIGITS = 10;

        if (digit1 < digit2) {
            swap(digit1, digit2);
        }
        for (int l = 1, total = 2; l <= MAX_NUM_OF_DIGITS; ++l, total <<= 1) {
            for (int mask = 0; mask < total; ++mask) {
                int64_t curr = 0;
                for (int bit = total >> 1; bit; bit >>= 1) {
                    curr = curr * 10 + ((mask & bit) ? digit1 : digit2);
                }
                if (k < curr && curr <= numeric_limits<int>::max() && curr % k == 0) {
                    return curr;
                }
            }
        }
        return -1; 
    }

