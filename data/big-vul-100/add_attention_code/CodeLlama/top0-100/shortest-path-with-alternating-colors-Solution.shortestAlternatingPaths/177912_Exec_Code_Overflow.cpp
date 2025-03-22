  tt_cmap12_validate( FT_Byte*      table,
                      FT_Validator  valid )
  {
    FT_Byte*   p;
    FT_ULong   length;
    FT_ULong   num_groups;


    if ( table + 16 > valid->limit )
      FT_INVALID_TOO_SHORT;

    p      = table + 4;
    length = TT_NEXT_ULONG( p );

    p          = table + 12;
     p          = table + 12;
     num_groups = TT_NEXT_ULONG( p );
 
    if ( table + length > valid->limit || length < 16 + 12 * num_groups )
       FT_INVALID_TOO_SHORT;
 
     /* check groups, they must be in increasing order */


      for ( n = 0; n < num_groups; n++ )
      {
        start    = TT_NEXT_ULONG( p );
        end      = TT_NEXT_ULONG( p );
        start_id = TT_NEXT_ULONG( p );

        if ( start > end )
          FT_INVALID_DATA;

        if ( n > 0 && start <= last )
          FT_INVALID_DATA;

        if ( valid->level >= FT_VALIDATE_TIGHT )
        {
          if ( start_id + end - start >= TT_VALID_GLYPH_COUNT( valid ) )
            FT_INVALID_GLYPH_ID;
        }

        last = end;
      }
    }


    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
        vector<vector<unordered_set<int>>> neighbors(n, vector<unordered_set<int>>(2));
        for (const auto& edge : red_edges) {
            neighbors[edge[0]][0].emplace(edge[1]);
        }
        for (const auto& edge : blue_edges) {
            neighbors[edge[0]][1].emplace(edge[1]);
        }
        const auto& INF = max(2 * n - 3, 0) + 1;
        vector<vector<int>> dist(n, vector<int>(2, INF));
        dist[0] = {0, 0};
        queue<pair<int, int>> q({{0, 0}, {0, 1}});
        while (!q.empty()) {
            int i, c;
            tie(i, c) = q.front(); q.pop();
            for (const auto& j : neighbors[i][c]) {
                if (dist[j][c] != INF) {
                    continue;
                }
                dist[j][c] = dist[i][1 ^ c] + 1;
                q.emplace(j, 1 ^ c);
            }
        }
        vector<int> result;
        for (const auto& d : dist) {
            const auto& x = *min_element(d.cbegin(), d.cend());
            result.emplace_back((x != INF) ? x : -1);
        }
        return result;
    }


