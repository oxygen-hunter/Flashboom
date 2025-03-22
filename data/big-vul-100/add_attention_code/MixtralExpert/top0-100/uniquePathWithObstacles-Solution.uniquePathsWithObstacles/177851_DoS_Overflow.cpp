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


        int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
            const int m = obstacleGrid.size();
            const int n = obstacleGrid[0].size();
            vector<int> v(n, 0);

            v[0] = 1;
            for(int i = 0; i < m; ++i) {
                if(obstacleGrid[i][0] != 0)
                    v[0] = 0;
                for(int j = 1; j < n; ++j) {
                    if(obstacleGrid[i][j] == 0)
                        v[j] += v[j - 1];
                    else
                        v[j] = 0;
                }
            }

            return v[n - 1];
        }


