parse_object(JsonLexContext *lex, JsonSemAction *sem)
{
	/*
	 * an object is a possibly empty sequence of object fields, separated by
	 * commas and surrounded by curly braces.
	 */
	json_struct_action ostart = sem->object_start;
    json_struct_action oend = sem->object_end;
    JsonTokenType tok;
 
    if (ostart != NULL)
        (*ostart) (sem->semstate);
 
	 * itself. Note that we increment this after we call the semantic routine
	 * for the object start and restore it before we call the routine for the
	 * object end.
	 */
	lex->lex_level++;

	/* we know this will succeeed, just clearing the token */
	lex_expect(JSON_PARSE_OBJECT_START, lex, JSON_TOKEN_OBJECT_START);

	tok = lex_peek(lex);
	switch (tok)
	{
		case JSON_TOKEN_STRING:
			parse_object_field(lex, sem);
			while (lex_accept(lex, JSON_TOKEN_COMMA, NULL))
				parse_object_field(lex, sem);
			break;
		case JSON_TOKEN_OBJECT_END:
			break;
		default:
			/* case of an invalid initial token inside the object */
			report_parse_error(JSON_PARSE_OBJECT_START, lex);
	}

	lex_expect(JSON_PARSE_OBJECT_NEXT, lex, JSON_TOKEN_OBJECT_END);

	lex->lex_level--;

	if (oend != NULL)
		(*oend) (sem->semstate);
}


    int maxProductPath(vector<vector<int>>& grid) {
        static const int MOD = 1e9 + 7;
        vector<vector<int64_t>> max_dp(2, vector<int64_t>(size(grid[0])));
        vector<vector<int64_t>> min_dp(2, vector<int64_t>(size(grid[0])));
        for (int i = 0; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]); ++j) {
                if (i == 0 && j == 0) {
                    max_dp[0][0] = min_dp[0][0] = grid[0][0];
                    continue;
                }
                auto curr_max = max(i > 0 ? max_dp[(i - 1) % 2][j] : max_dp[i % 2][j - 1],
                                    j > 0 ? max_dp[i % 2][j - 1] : max_dp[(i - 1) % 2][j]);
                auto curr_min = min(i > 0 ? min_dp[(i - 1) % 2][j] : min_dp[i % 2][j - 1],
                                    j > 0 ? min_dp[i % 2][j - 1] : min_dp[(i - 1) % 2][j]);
                if (grid[i][j] < 0) {
                    swap(curr_max, curr_min);
                }
                max_dp[i % 2][j] = curr_max * grid[i][j];
                min_dp[i % 2][j] = curr_min * grid[i][j];
            }
        }
        return max_dp[(size(grid) - 1) % 2].back() >= 0 ? max_dp[(size(grid) - 1) % 2].back() % MOD : -1;
    }


