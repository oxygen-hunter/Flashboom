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

    int minimumSeconds(vector<vector<string>>& land) {
        static const vector<pair<int, int>> DIRECTIONS {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        vector<vector<int>> lookup1(size(land), vector<int>(size(land[0]), -1));
        vector<vector<int>> lookup2(size(land), vector<int>(size(land[0]), -1));
        vector<pair<int, int>> q1;
        vector<pair<int, int>> q2;
        for (int i = 0; i < size(land); ++i) {
            for (int j = 0; j < size(land[0]); ++j) {
                if (land[i][j] == "*") {
                    q1.emplace_back(i, j);
                    lookup2[i][j] = 0;
                } else if (land[i][j] == "S") {
                    q2.emplace_back(i, j);
                    lookup2[i][j] = 0;
                }
            }
        }
        while (!empty(q1) || !empty(q2)) {
            vector<pair<int, int>> new_q1;
            vector<pair<int, int>> new_q2;
            for (const auto& [i, j] : q1) {
                for (const auto& [di, dj] : DIRECTIONS) {
                    const int ni = i + di, nj = j + dj;
                    if (!(0 <= ni && ni < size(land) && 0 <= nj && nj < size(land[0]) && land[ni][nj] != "X" && land[ni][nj] != "D" && lookup1[ni][nj] == -1)) {
                        continue;
                    }
                    lookup1[ni][nj] = 0;
                    new_q1.emplace_back(ni, nj);
                }
            }
            for (const auto& [i, j] : q2) {
                if (land[i][j] == "D") {
                    return lookup2[i][j];
                }
                for (const auto& [di, dj] : DIRECTIONS) {
                    const int ni = i + di, nj = j + dj;
                    if (!(0 <= ni && ni < size(land) && 0 <= nj && nj < size(land[0]) && land[ni][nj] != "X" && lookup2[ni][nj] == -1 && lookup1[ni][nj] == -1)) {
                        continue;
                    }
                    lookup2[ni][nj] = lookup2[i][j] + 1;
                    new_q2.emplace_back(ni, nj);
                }
            }
            q1 = move(new_q1);
            q2 = move(new_q2);
        }
        return -1;
    }

