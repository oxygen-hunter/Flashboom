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

    vector<int> findXSum(vector<int>& nums, int k, int x) {
        using ordered_set = tree<pair<int, int>, null_type, greater<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update>;
        ordered_set os;
        unordered_map<int, int> cnt;
        const auto& update = [&](int v, int d, int curr) {
            if (d == 1) {
                os.insert({cnt[v], v});
            }

            if (os.order_of_key(pair(cnt[v], v)) < x) {
                curr += d * cnt[v] * v;
                if (x < size(os)) {
                    const auto [nc, nv] = *(os.find_by_order(x));
                    curr -= d * nc * nv;
                }
            }
            if (d != 1) {
                os.erase(pair(cnt[v], v));
            }
            return curr;
        };

        vector<int> result;
        for (int i = 0, curr = 0; i < size(nums); ++i) {
            if (cnt.count(nums[i])) {
                curr = update(nums[i], -1, curr);
            }
            ++cnt[nums[i]];
            curr = update(nums[i], +1, curr);
            if (i < k - 1) {
                continue;
            }
            result.emplace_back(curr);
            curr = update(nums[i - (k - 1)], -1, curr);
            --cnt[nums[i - (k - 1)]];
            if (cnt[nums[i - (k - 1)]]) {
                curr = update(nums[i - (k - 1)], +1, curr);
            } else {
                cnt.erase(nums[i - (k - 1)]);
            }
        }
        return result;
    }

