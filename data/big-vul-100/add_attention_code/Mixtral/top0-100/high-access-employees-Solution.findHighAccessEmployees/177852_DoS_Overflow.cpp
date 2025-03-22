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

    vector<string> findHighAccessEmployees(vector<vector<string>>& access_times) {
        static const int LIMIT_COUNT = 2;
        static const int LIMIT_MINUTE = 60;
    
        const auto& to_minute = [](const auto& s) {
            return stoi(s.substr(0, 2)) * 60 + stoi(s.substr(2));
        };
    
        unordered_map<string, vector<int>> lookup;;
        for (const auto& x : access_times) {
            lookup[x[0]].emplace_back(to_minute(x[1]));
        }
        vector<string> result;
        for (auto& [x, ts] : lookup) {
            sort(begin(ts), end(ts));
            for (int i = 0; i + LIMIT_COUNT < size(ts); ++i) {
                if (!(ts[i] + LIMIT_MINUTE <= ts[i + LIMIT_COUNT])) {
                    result.emplace_back(x);
                    break;
                }
            } 
        }
        return result;
    }

