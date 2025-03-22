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


    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        unordered_map<int, int> cnt1;
        for (const auto& x : nums) {
            ++cnt1[x];
        }
        vector<int64_t> cnt2(ranges::max(nums) + 1);
        for (int g = size(cnt2) - 1; g >= 1; --g) {
            int64_t c = 0;
            for (int ng = g; ng < size(cnt2); ng += g) {
                c += cnt1[ng];
            }
            cnt2[g] = c * (c - 1) / 2;
            for (int ng = g + g; ng < size(cnt2); ng += g) {
                cnt2[g] -= cnt2[ng];
            }
        }
        vector<int64_t> prefix(size(cnt2) + 1);
        for (int i = 0; i < size(prefix) - 1; ++i) {
            prefix[i + 1] += prefix[i] + cnt2[i];
        }
        vector<int> result(size(queries));
        for (int i = 0; i < size(queries); ++i) {
            result[i] = distance(cbegin(prefix), upper_bound(cbegin(prefix), cend(prefix), queries[i])) - 1;
        }
        return result;
    }


