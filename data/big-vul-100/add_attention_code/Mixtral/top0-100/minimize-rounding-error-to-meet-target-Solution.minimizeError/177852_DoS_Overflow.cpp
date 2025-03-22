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

    string minimizeError(vector<string>& prices, int target) {
        vector<double> errors;
        int lower = 0, upper = 0;
        for (const auto& price : prices) {
            const auto& p = stod(price);
            lower += floor(p);
            upper += ceil(p);
            if (p != floor(p)) {
                errors.emplace_back(p - floor(p));
            }
        }
        if (target < lower || target > upper) {
            return "-1";
        }

        int lower_round_count = upper - target;
        nth_element(errors.begin(), errors.begin() + lower_round_count, errors.end());
        double min_error = 0.0;
        for (int i = 0; i < errors.size(); ++i) {
            if (i < lower_round_count) {
                min_error += errors[i];
            } else {
                min_error += 1.0 - errors[i];
            }
        }
        const auto& result = to_string(min_error);
        return result.substr(0, result.find(".") + 4);
    }

