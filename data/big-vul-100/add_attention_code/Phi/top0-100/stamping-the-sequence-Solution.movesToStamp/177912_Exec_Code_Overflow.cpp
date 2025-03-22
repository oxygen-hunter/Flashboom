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

    vector<int> movesToStamp(string stamp, string target) {
        const int M = stamp.size(), N = target.size();
        
        queue<int> q;
        vector<bool> lookup(N);
        vector<int> result;
        vector<pair<unordered_set<int>, unordered_set<int>>> A;
        for (int i = 0; i < N - M + 1; ++i) {
            unordered_set<int> made, todo;
            for (int j = 0; j < M; ++j) {
                if (stamp[j] == target[i + j]) {
                    made.emplace(i + j);
                } else {
                    todo.emplace(i + j);
                }
            }
            A.emplace_back(made, todo);
            if (!todo.empty()) {
                continue;
            }
            result.emplace_back(i);
            for (const auto& m : made) {
                if (lookup[m]) {
                    continue;
                }
                q.emplace(m);
                lookup[m] = true;
            }
        }
        
        while (!q.empty()) {
            auto i = q.front(); q.pop();
            for (int j = max(0, i - M + 1); j < min(N - M, i) + 1; ++j) {
                unordered_set<int>& made = A[j].first;
                unordered_set<int>& todo = A[j].second;
                if (!todo.count(i)) {
                    continue;
                }
                todo.erase(i);
                if (!todo.empty()) {
                    continue;
                }
                result.emplace_back(j);
                for (const auto& m : made) {
                    if (lookup[m]) {
                        continue;
                    }
                    q.emplace(m);
                    lookup[m] = true;
                }
            }
        }
        if (std::all_of(lookup.cbegin(), lookup.cend(), [](bool i){ return i; })) {
            reverse(result.begin(), result.end());
            return result;
        }
        return {};
    }

