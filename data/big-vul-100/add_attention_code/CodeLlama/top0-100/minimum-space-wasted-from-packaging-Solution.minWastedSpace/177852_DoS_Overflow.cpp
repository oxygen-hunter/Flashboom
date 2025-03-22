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


    int minWastedSpace(vector<int>& packages, vector<vector<int>>& boxes) {
        static const int MOD = 1e9 + 7;
        static const int64_t INF = numeric_limits<int64_t>::max();

        sort(begin(packages), end(packages));
        int64_t result = INF;
        for (auto& box : boxes) {
            sort(begin(box), end(box));
            if (box.back() < packages.back()) {
                continue;
            }
            int64_t curr = 0;
            auto left = cbegin(packages);
            for (const auto& b : box) {
                auto right = upper_bound(left, cend(packages), b);
                curr += b * (right - left);
                left = right;
            }
            result = min(result, curr);
        }
        int64_t total = accumulate(cbegin(packages), cend(packages), 0LL);
        return result != INF ? (result - total) % MOD : -1;
    }


