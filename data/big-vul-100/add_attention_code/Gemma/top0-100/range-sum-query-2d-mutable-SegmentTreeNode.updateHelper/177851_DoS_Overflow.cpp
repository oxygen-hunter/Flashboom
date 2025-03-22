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


    void updateHelper(SegmentTreeNode *root, const pair<int, int>& i, int val) {
        // Out of range.
        if (root == nullptr ||
            (root->start.first > i.first || root->start.second > i.second) ||
            (root->end.first < i.first || root->end.second < i.second)) {
            return;
        }

        // Change the node's value with [i] to the new given value.
        if ((root->start.first == i.first && root->start.second == i.second) &&
            (root->end.first == i.first && root->end.second == i.second)) {
            root->sum = val;
            return;
        }
        for (auto& node : root->neighbor) {
            updateHelper(node, i, val);
        }

        root->sum = 0;
        for (auto& node : root->neighbor) {
            if (node) {
                root->sum += node->sum;
            }
        }
    }


