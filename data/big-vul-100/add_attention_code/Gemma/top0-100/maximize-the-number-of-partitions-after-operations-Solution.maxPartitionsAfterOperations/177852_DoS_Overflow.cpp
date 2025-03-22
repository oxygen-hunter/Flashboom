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


    int maxPartitionsAfterOperations(string s, int k) {
        vector<int> left(size(s) + 1);
        vector<int> left_mask(size(s) + 1);
        for (int i = 0, cnt = 0, mask = 0; i < size(s); ++i) {
            mask |= 1 << (s[i] - 'a');
            if (__builtin_popcount(mask) > k) {
                ++cnt;
                mask = 1 << (s[i] - 'a');
            }
            left[i + 1] = cnt;
            left_mask[i + 1] = mask;
        }
        vector<int> right(size(s) + 1);
        vector<int> right_mask(size(s) + 1);
        for (int i = size(s) - 1, cnt = 0, mask = 0; i >= 0; --i) {
            mask |= 1 << (s[i] - 'a');
            if (__builtin_popcount(mask) > k) {
                ++cnt;
                mask = 1 << (s[i] - 'a');
            }
            right[i] = cnt;
            right_mask[i] = mask;
        }

        int result = 0;
        for (int i = 0; i < size(s); ++i) {
            int curr = left[i] + right[i + 1];
            const int mask = left_mask[i] | right_mask[i + 1];
            if (__builtin_popcount(left_mask[i]) == k && __builtin_popcount(right_mask[i + 1]) == k && __builtin_popcount(mask) != 26) {
                curr += 3;
            } else if (__builtin_popcount(mask) + (__builtin_popcount(mask) != 26 ? 1 : 0) > k) {  // test case: s = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", k = 26
                curr += 2;
            } else {
                curr += 1;
            }
            result = max(result, curr);
        }
        return result;
    }


