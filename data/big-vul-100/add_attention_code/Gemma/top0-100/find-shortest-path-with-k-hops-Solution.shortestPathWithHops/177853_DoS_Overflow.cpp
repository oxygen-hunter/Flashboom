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


    int shortestPathWithHops(int n, vector<vector<int>>& edges, int s, int d, int k) {
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].emplace_back(e[1], e[2]);
            adj[e[1]].emplace_back(e[0], e[2]);
        }
        const auto& modified_dijkstra = [&]() {
            static const int INF = numeric_limits<int>::max();

            vector<vector<int>> best(size(adj), vector<int>(k + 1, INF));
            best[s][0] = 0;
            priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> min_heap;
            min_heap.emplace(best[s][0], s, 0);
            while (!empty(min_heap)) {
                const auto [curr, u, cnt] = min_heap.top(); min_heap.pop();
                if (curr > best[u][cnt]) {
                    continue;
                }
                if (u == d) {
                    return curr;
                }
                for (const auto& [v, w] : adj[u]) {
                    if (w < best[v][cnt] - curr) {
                        best[v][cnt] = curr + w;
                        min_heap.emplace(best[v][cnt], v, cnt);
                    }
                    if (cnt + 1 <= k && curr < best[v][cnt + 1]) {
                        best[v][cnt + 1] = curr;
                        min_heap.emplace(best[v][cnt + 1], v, cnt + 1);
                    }
                }
            }
            return -1;
        };

        return modified_dijkstra();
    }


