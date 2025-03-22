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

    int magnificentSets(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            adj[e[0] - 1].emplace_back(e[1] - 1);
            adj[e[1] - 1].emplace_back(e[0] - 1);
        }
        vector<bool> lookup(n);
        const auto& bfs = [&](int u) {
            vector<int> group = {u};
            vector<int> q = {u};
            lookup[u] = true;
            while (!empty(q)) {
                vector<int> new_q;
                for (const auto& u : q) {
                    group.emplace_back(u);
                    for (const auto& v : adj[u]) {
                        if (lookup[v]) {
                            continue;
                        }
                        lookup[v] = true;
                        new_q.emplace_back(v);
                    }
                }
                q = move(new_q);
            }
            return group;
        };
        const auto& bfs2 = [&](int u) {
            int result = 0;
            vector<bool> lookup(n);
            unordered_set<int> q = {u};
            lookup[u] = true;
            for (; !empty(q); ++result) {
                unordered_set<int> new_q;
                for (const auto& u : q) {
                    for (const auto& v : adj[u]) {
                        if (q.count(v)) {
                            return 0;
                        }
                        if (lookup[v]) {
                            continue;
                        }
                        lookup[v] = true;
                        new_q.emplace(v);
                    }
                }
                q = move(new_q);
            }
            return result;
        };

        int result = 0;
        for (int u = 0; u < n; ++u) {
            if (lookup[u]) {
                continue;
            }
            const auto& group = bfs(u);
            int mx = 0;
            for (const auto& u : group) {
                const int d = bfs2(u);
                if (d == 0) {
                    return -1;
                }
                mx = max(mx, d);
            }
            result += mx;
        }
        return result;
    }

