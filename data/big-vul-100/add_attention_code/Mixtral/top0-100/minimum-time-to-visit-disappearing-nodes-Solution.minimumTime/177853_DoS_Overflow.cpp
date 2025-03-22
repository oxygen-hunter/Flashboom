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

    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
        static const int INF = numeric_limits<int>::max();
    
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].emplace_back(e[1], e[2]);
            adj[e[1]].emplace_back(e[0], e[2]);
        }
        const auto& modified_dijkstra = [&](int start) {
            vector<int> best(n, -1);
            best[start] = 0;
            priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>, greater<pair<int64_t, int>>> min_heap;
            min_heap.emplace(best[start], start);
            while (!empty(min_heap)) {
                const auto [curr, u] = min_heap.top(); min_heap.pop();
                if (curr != best[u]) {
                    continue;
                }
                for (auto [v, w] : adj[u]) {
                    if (!(w < min(best[v] != -1 ? best[v] : INF, disappear[v]) - curr)) {  // modified
                        continue;
                    }
                    best[v] = curr + w;
                    min_heap.emplace(best[v],  v);
                }
            }
            return best;
        };
    
        return modified_dijkstra(0);
    }

