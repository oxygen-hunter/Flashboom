setPath(JsonbIterator **it, Datum *path_elems,
		bool *path_nulls, int path_len,
		JsonbParseState **st, int level, Jsonb *newval, bool create)
{
	JsonbValue	v;
    JsonbValue *res = NULL;
    int         r;
 
    if (path_nulls[level])
        elog(ERROR, "path element at the position %d is NULL", level + 1);
	switch (r)
	{
		case WJB_BEGIN_ARRAY:
			(void) pushJsonbValue(st, r, NULL);
			setPathArray(it, path_elems, path_nulls, path_len, st, level,
						 newval, v.val.array.nElems, create);
			r = JsonbIteratorNext(it, &v, false);
			Assert(r == WJB_END_ARRAY);
			res = pushJsonbValue(st, r, NULL);

			break;
		case WJB_BEGIN_OBJECT:
			(void) pushJsonbValue(st, r, NULL);
			setPathObject(it, path_elems, path_nulls, path_len, st, level,
						  newval, v.val.object.nPairs, create);
			r = JsonbIteratorNext(it, &v, true);
			Assert(r == WJB_END_OBJECT);
			res = pushJsonbValue(st, r, NULL);

			break;
		case WJB_ELEM:
		case WJB_VALUE:
			res = pushJsonbValue(st, r, &v);
			break;
		default:
			elog(ERROR, "impossible state");
	}

	return res;
}

    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> lookup;
        for (const auto& pair : knowledge) {
            lookup[pair[0]] = pair[1];
        }
        string result, curr;
        bool has_pair = false;;
        for (int i = 0; i < size(s); ++i) {
            if (s[i] == '(') {
                has_pair = true;
            } else if (s[i] == ')') {
                has_pair = false;
                if (lookup.count(curr)) {
                    for (const auto& c : lookup[curr]) {
                        result.push_back(c);
                    }
                } else {
                    result.push_back('?');
                }
                curr.clear();
            } else if (has_pair) {
                curr.push_back(s[i]);
            } else {
                result.push_back(s[i]);
            }
        }
        return result;
    }

