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

    int mincostTickets(vector<int>& days, vector<int>& costs) {
        static vector<int> durations{1, 7, 30};
        
        const int W = durations.back();
        vector<int> dp(W, numeric_limits<int>::max());
        dp[0] = 0;
        vector<int> last_buy_days{0, 0, 0};
        for (int i = 1; i < days.size() + 1; ++i) {
            dp[i % W] = numeric_limits<int>::max();
            for (int j = 0; j < durations.size(); ++j) {
                while (i - 1 < days.size() &&
                       days[i - 1] > days[last_buy_days[j]] + durations[j] - 1) {
                    ++last_buy_days[j];  // Time: O(n)
                }
                dp[i % W] = min(dp[i % W], dp[last_buy_days[j] % W] + costs[j]);
            }
        }
        return dp[days.size() % W];
    }

