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


