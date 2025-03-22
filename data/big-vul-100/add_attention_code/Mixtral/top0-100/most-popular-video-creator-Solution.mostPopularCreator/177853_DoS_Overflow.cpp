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

    vector<vector<string>> mostPopularCreator(vector<string>& creators, vector<string>& ids, vector<int>& views) {
        unordered_map<string, int> cnt;
        unordered_map<string, pair<int, string>> lookup;
        for (int i = 0; i < size(creators); ++i) {
            cnt[creators[i]] += views[i];
            if (!lookup.count(creators[i])) {
                lookup[creators[i]] = {-views[i], ids[i]};
                continue;
            }
            lookup[creators[i]] = min(lookup[creators[i]], pair(-views[i], ids[i]));
        }
        int mx = 0;
        for (const auto& [_, v] : cnt) {
            mx = max(mx, v);
        }
        vector<vector<string>> result;
        for (const auto& [k, v] : cnt) {
            if (v != mx) {
                continue;
            }
            result.push_back({k, lookup[k].second});
        }
        return result;
    }

