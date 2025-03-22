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

    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        static const double PI = atan2(0, -1);

        vector<double> arr;
        int extra = 0;
        for (const auto& p : points) {
            if (p == location) {
                ++extra;
                continue;
            }
            arr.emplace_back(atan2(p[1] - location[1], p[0] - location[0]));
        }
        sort(begin(arr), end(arr));
        const int n = size(arr);
        for (int i = 0; i < n; ++i) {  // make it circular
            arr.emplace_back(arr[i] + 2.0 * PI);
        }
        const double d = 2.0 * PI * (angle / 360.0);
        int result = 0;
        for (int left = 0, right = 0; right < size(arr); ++right) {
            while (arr[right] - arr[left] > d) {
                ++left;
            }
            result = max(result, right - left + 1);
        }
        return result + extra;
    }

