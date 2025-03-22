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

    int smallestRepunitDivByK(int K) {
        // by observation, K % 2 = 0 or K % 5 = 0, it is impossible
        if (K % 2 == 0 || K % 5 == 0) {
            return -1;
        }
        // let f(N) is a N-length integer only containing digit 1
        // given K % 2 != 0 and K % 5 != 0
        // if there is no N in range (1..K) s.t. f(N) % K = 0
        // => there must be K remainders of f(N) % K in range (1..K-1) excluding 0
        // => due to pigeonhole principle, there must be at least 2 same remainders
        // => there must be some x, y in range (1..K) and x > y s.t. f(x) % K = f(y) % K
        // => (f(x) - f(y)) % K = 0
        // => (f(x-y) * 10^y) % K = 0
        // => due to (x-y) in range (1..K)
        // => f(x-y) % K != 0
        // => 10^y % K = 0
        // => K % 2 = 0 or K % 5 = 0
        // => -><-
        // it proves that there must be some N in range (1..K) s.t. f(N) % K = 0
        int result = 0;
        for (int N = 1; N <= K; ++N) {
            result = (result * 10 + 1) % K;
            if (!result) {
                return N;
            }
        }
        assert(false);
        return -1;  // never reach
    }

