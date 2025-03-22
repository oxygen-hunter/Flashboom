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

    int largestPathValue(string colors, vector<vector<int>>& edges) {
        vector<vector<int>> adj(size(colors));
        vector<int> in_degree(size(colors));
        for (const auto& edge : edges) {
            adj[edge[0]].emplace_back(edge[1]);
            ++in_degree[edge[1]];
        }
        vector<int> q;
        for (int i = 0; i < size(colors); ++i) {
            if (!in_degree[i]) {
                q.emplace_back(i);
            }
        }
        vector<vector<int>> dp(size(colors), vector<int>(26));
        int result = -1, cnt = 0;
        while (!empty(q)) {
            vector<int> new_q;
            for (const auto& u : q) {
                ++cnt;
                result = max(result, ++dp[u][colors[u] - 'a']);
                for (const auto& v : adj[u]) {
                    for (int c = 0; c < 26; ++c) {
                        dp[v][c] = max(dp[v][c], dp[u][c]);
                    }
                    if (!--in_degree[v]) {
                        new_q.emplace_back(v);
                    }
                }
            }
            q = move(new_q);
        }
        return cnt == size(colors) ? result : -1;
    }

