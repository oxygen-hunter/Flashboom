  tt_cmap10_validate( FT_Byte*      table,
                      FT_Validator  valid )
  {
    FT_Byte*  p = table + 4;
    FT_ULong  length, count;


    if ( table + 20 > valid->limit )
      FT_INVALID_TOO_SHORT;

    length = TT_NEXT_ULONG( p );
     p      = table + 16;
     count  = TT_NEXT_ULONG( p );
 
    if ( table + length > valid->limit || length < 20 + count * 2 )
       FT_INVALID_TOO_SHORT;
 
     /* check glyph indices */
    {
      FT_UInt  gindex;


      for ( ; count > 0; count-- )
      {
        gindex = TT_NEXT_USHORT( p );
        if ( gindex >= TT_VALID_GLYPH_COUNT( valid ) )
          FT_INVALID_GLYPH_ID;
      }
    }

    return SFNT_Err_Ok;
  }

    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        static const int MOD = 1e9 + 7;
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& e : edges) {
            int u = e[0] - 1, v = e[1] - 1, w = e[2];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        vector<int> dist(n, numeric_limits<int>::max()), dp(n);
        dist[n - 1] = 0;
        dp[n - 1] = 1;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
        min_heap.emplace(0, n - 1);
        while (!empty(min_heap)) {
            const auto [w, u] = min_heap.top(); min_heap.pop();
            if (w > dist[u]) {
                continue;
            }
            for (const auto& [v, d] : adj[u]) {
                if (w + d < dist[v]) {
                    dist[v] = w + d;
                    min_heap.emplace(dist[v], v);
                } else if (w > dist[v]) {
                    dp[u] = (dp[u] + dp[v]) % MOD;
                }
            }
            if (u == 0) {  // early return
                break;
            }
        }
        return dp[0];
    }

