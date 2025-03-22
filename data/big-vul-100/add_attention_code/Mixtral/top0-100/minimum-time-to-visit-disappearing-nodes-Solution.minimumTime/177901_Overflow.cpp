_asn1_ltostr (long v, char *str)
 {
   long d, r;
   char temp[LTOSTR_MAX_SIZE];
  int count, k, start;

  if (v < 0)
    {
      str[0] = '-';
      start = 1;
      v = -v;
    }
  else
    start = 0;

  count = 0;
  do
    {
      d = v / 10;
      r = v - d * 10;
      temp[start + count] = '0' + (char) r;
       count++;
       v = d;
     }
  while (v);
 
   for (k = 0; k < count; k++)
     str[k + start] = temp[start + count - k - 1];
  str[count + start] = 0;
  return str;
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

