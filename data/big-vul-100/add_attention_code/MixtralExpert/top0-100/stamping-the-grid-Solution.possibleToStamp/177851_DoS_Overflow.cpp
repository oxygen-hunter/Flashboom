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


    bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) {
        vector<vector<int>> prefix(size(grid) + 1, vector<int>(size(grid[0]) + 1));
        vector<vector<int>> fit(size(grid), vector<int>(size(grid[0])));
        for (int i = 0; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]); ++j) {
                prefix[i + 1][j + 1] = prefix[i + 1][j] + prefix[i][j + 1] - prefix[i][j] + (1 ^ grid[i][j]);
                if (i + 1 >= stampHeight && j + 1 >= stampWidth) {
                    const int x = i + 1 - stampHeight, y = j + 1 - stampWidth;
                    fit[i][j] = static_cast<int>(prefix[i + 1][j + 1] - prefix[x][j + 1] - prefix[i + 1][y] + prefix[x][y] == stampWidth * stampHeight);
                }
            }
        }
        vector<vector<int>> prefix2(size(grid) + 1, vector<int>(size(grid[0]) + 1));
        for (int i = 0; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]); ++j) {
                prefix2[i + 1][j + 1] = prefix2[i + 1][j] + prefix2[i][j + 1] - prefix2[i][j] + fit[i][j];
            }
        }
        for (int i = 0; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]); ++j) {
                const int x = min(i + stampHeight, static_cast<int>(size(grid))), y = min(j + stampWidth, static_cast<int>(size(grid[0])));
                if (!grid[i][j] && !(prefix2[x][y] - prefix2[i][y] - prefix2[x][j] + prefix2[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }


