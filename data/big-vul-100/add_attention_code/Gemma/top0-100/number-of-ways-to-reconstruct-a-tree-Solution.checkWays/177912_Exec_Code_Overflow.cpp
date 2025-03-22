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


    int checkWays(vector<vector<int>>& pairs) {
        unordered_map<int, unordered_set<int>> adj;
        for (const auto& pair : pairs) {
            adj[pair[0]].emplace(pair[1]);
            adj[pair[1]].emplace(pair[0]);
        }
        int n = size(adj);
        bool mul = false;
        unordered_set<int> lookup;
        vector<int> nodes;
        transform(begin(adj), end(adj), back_inserter(nodes),
                  [](const auto& kvp) { return kvp.first; });
        sort(begin(nodes), end(nodes),
             [&adj](const auto& a, const auto& b) {
                 return size(adj[a]) > size(adj[b]);
             });
        for (const auto& node : nodes) {
            lookup.emplace(node);
            int parent = 0;
            for (const auto& x : adj[node]) {
                if (!lookup.count(x)) {
                    continue;
                }
                if (parent == 0 || size(adj[x]) < size(adj[parent])) {
                    parent = x;
                }
            }
            if (parent) {
                for (const auto& x : adj[node]) {
                    if (x != parent && !adj[parent].count(x)) {
                        return 0;
                    }
                }
                mul |= size(adj[node]) == size(adj[parent]);
            } else if (size(adj[node]) != n - 1) {
                return 0;
            }
        }
        return 1 + mul;
    }


