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


    int minAbsDifference(vector<int>& nums, int goal) {
        int mx = 0, mn = 0;
        for (const auto& x : nums) {
            if (x > 0) {
                mx += x;
            } else if (x < 0) {
                mn += x;
            }
        }
        if (goal > mx) {
            return goal - mx;
        }
        if (goal < mn) {
            return mn - goal;
        }
        int result = abs(goal);
        unordered_set<int> sums1{0};
        for (auto i = 0; i < size(nums) / 2; ++i) {
            for (const auto& x : vector<int>(cbegin(sums1), cend(sums1))) {
                if (!sums1.emplace(x + nums[i]).second) {
                    continue;
                }
                result = min(result, abs(goal - x - nums[i]));  // case of right half part is 0
            }
        }
        vector<int> sorted_sums1(cbegin(sums1), cend(sums1));  // Space: O(2^(n/2))
        sort(begin(sorted_sums1), end(sorted_sums1));  // Time: O((n/2) * 2^(n/2)) = O(n * 2^(n/2))
        unordered_set<int> sums2{0};
        for (int i = size(nums) / 2; i < size(nums); ++i) {
            for (const auto& x : vector<int>(cbegin(sums2), cend(sums2))) {
                if (!sums2.emplace(x + nums[i]).second) {
                    continue;
                }
                auto cit = lower_bound(cbegin(sorted_sums1), cend(sorted_sums1), goal - x - nums[i]);  // Time: O(2^(n/2)) * O(n/2)
                if (cit != cend(sorted_sums1)) {
                    result = min(result, abs(goal - x - nums[i] - *cit));
                }
                if (cit != cbegin(sorted_sums1)) {
                    result = min(result, abs(goal - x - nums[i] - *prev(cit)));
                }
                if (result == 0) {
                    return result;
                }
            }
        }
        return result;
    }


