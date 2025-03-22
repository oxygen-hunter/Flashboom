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


    vector<double> sampleStats(vector<int>& count) {
        const double mi = distance(count.cbegin(), find_if(count.cbegin(), count.cend(), 
                                   [](int x) { return x != 0; }));
        
        const double ma = count.size() - 1 - 
                          distance(count.crbegin(), find_if(count.crbegin(), count.crend(), 
                                   [](int x) { return x != 0; }));
        
        const auto& n = accumulate(count.cbegin(), count.cend(), 0);
        double total = 0.0;
        for (int i = 0; i < count.size(); ++i) {
            total += double(i) * count[i];
        }
        const double mean = total / n;
        
        const double mode = distance(count.cbegin(), max_element(count.cbegin(), count.cend()));
        
        for (int i = 1; i < count.size(); ++i) {
            count[i] += count[i - 1];
        }
        const auto& median1 = distance(count.cbegin(), lower_bound(count.cbegin(), count.cend(), (n + 1) / 2));
        const auto& median2 = distance(count.cbegin(), lower_bound(count.cbegin(), count.cend(), (n + 2) / 2));
        const double median = (median1 + median2) / 2.0;
        
        return {mi, ma, mean, median, mode};
    }


