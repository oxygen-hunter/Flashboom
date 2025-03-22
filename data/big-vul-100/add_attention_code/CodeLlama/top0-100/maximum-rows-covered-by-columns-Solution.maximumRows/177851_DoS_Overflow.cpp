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


    int maximumRows(vector<vector<int>>& matrix, int numSelect) {
        const auto& next_popcount = [](uint32_t n) {  // reference: https://massivealgorithms.blogspot.com/2014/06/hakmem-item-175.html
            const uint32_t lowest_bit = n & -n;
            const uint32_t left_bits = n + lowest_bit;
            const uint32_t changed_bits = n ^ left_bits;
            const uint32_t right_bits = (changed_bits / lowest_bit) >> 2;
            return left_bits | right_bits;
        };

        vector<uint32_t> masks(size(matrix));
        for (int r = 0; r < size(matrix); ++r) {
            uint32_t m = 0;
            for (int c = 0; c < size(matrix[0]); ++c) {
                m |= matrix[r][c] << ((size(matrix[0]) - 1) - c);
            }
            masks[r] = m;
        }
        int result = 0;
        for (uint32_t mask = (1 << numSelect) - 1; mask < 1 << size(matrix[0]); mask = next_popcount(mask)) {
            const int cnt = accumulate(cbegin(masks), cend(masks), 0, [&](const auto& total, const auto& x) {
                return total + static_cast<int>((x & mask) == x);
            });
            result = max(result, cnt);
        }
        return result;
    }


