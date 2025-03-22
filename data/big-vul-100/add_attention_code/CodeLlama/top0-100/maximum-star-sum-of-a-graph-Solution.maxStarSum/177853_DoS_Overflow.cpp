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


    int maxStarSum(vector<int>& vals, vector<vector<int>>& edges, int k) {
        vector<vector<int>> adj(size(vals));
        for (const auto& e : edges) {
            if (vals[e[1]] > 0) {
                adj[e[0]].emplace_back(e[1]);
            }
            if (vals[e[0]] > 0) {
                adj[e[1]].emplace_back(e[0]);
            }
        }
        int result = numeric_limits<int>::min();
        for (int u = 0; u < size(vals); ++u) {
            if (1 <= k && k <= size(adj[u])) {
                nth_element(begin(adj[u]), begin(adj[u]) + k - 1, end(adj[u]),
                            [&](const auto& a, const auto& b) {
                                return vals[a] > vals[b];
                            });
            }
            result = max(result, vals[u] + accumulate(cbegin(adj[u]), cbegin(adj[u]) + min(k, static_cast<int>(size(adj[u]))), 0,
                                                      [&](const auto& total, const auto& x) {
                                                          return total + vals[x];
                                                      }));
        }
        return result;
    }


