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


    TreeNode* deserializeHelper(int minVal, int maxVal, const string& data, int *i) {
        if (*i == data.length()) {
            return nullptr;
        }
        int j = data.find(' ', *i);
        auto val = stoi(data.substr(*i, j - *i));
        if (minVal < val && val < maxVal) {
            auto node = new TreeNode(val);
            *i = j + 1;
            node->left = deserializeHelper(minVal, val, data, i);
            node->right = deserializeHelper(val, maxVal, data, i);
            return node;
        } else {
            return nullptr;
        }
    }


