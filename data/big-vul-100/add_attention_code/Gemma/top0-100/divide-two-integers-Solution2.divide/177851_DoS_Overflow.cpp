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


    int divide(int dividend, int divisor) {
        long long result = 0;
        long long a = llabs(dividend);
        long long b = llabs(divisor);

        int shift = 31;
        while (shift >= 0) {
            if (a >= b << shift) {
                a -= b << shift;
                result += 1LL << shift;
            }
            --shift;
        }

        result = ((dividend ^ divisor) >> 31) ? -result : result;
        return min(result, static_cast<long long>(numeric_limits<int>::max()));
    }


