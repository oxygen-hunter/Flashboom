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


    int maxScore(vector<int>& nums) {
        vector<int> dp(1 << size(nums));
        for (int mask = 3; mask < size(dp); ++mask) {
            int cnt = __builtin_popcount(mask);
            if (cnt % 2) {
                continue;
            }
            vector<int> bits;
            for (int i = 0, m = mask; m; ++i, m >>= 1) {
                if (m & 1) {
                    bits.emplace_back(i);
                }
            }
            for (int i = 0; i < size(bits); ++i) {
                for (int j = i + 1; j < size(bits); ++j) {
                    dp[mask] = max(dp[mask], cnt / 2 * gcd(nums[bits[i]], nums[bits[j]]) + dp[mask ^ (1 << bits[i]) ^ (1 << bits[j])]);
                }
            }
        }
        return dp.back();
    }


