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

    long long maximumValueSum(vector<vector<int>>& board) {
        static const int k = 3;
    
        const auto& combinations = [](int n, int k, const auto& callback) {
            static const auto& next_pos =
                [](const auto& n, const auto& k, const auto& idxs) {
                    int i = k - 1;
                    for (; i >= 0; --i) {
                        if (idxs[i] != i + n - k) {
                            break;
                        }
                    }
                    return i;
                };
        
            vector<int> idxs(k);
            iota(begin(idxs), end(idxs), 0);
            callback(idxs);
            for (int i; (i = next_pos(n, k, idxs)) >= 0;) {
                ++idxs[i];
                for (int j = i + 1; j < k; ++j) {
                    idxs[j] = idxs[j - 1] + 1;
                }
                callback(idxs);
            }
        };
    
        using Data = tuple<int, int, int>;
        vector<priority_queue<Data, vector<Data>, greater<Data>>> min_heaps(size(board[0]));
        for (int i = 0; i < size(board); ++i) {
            priority_queue<Data, vector<Data>, greater<Data>> min_heap;
            for (int j = 0; j < size(board[0]); ++j) {
                min_heap.emplace(board[i][j], i, j);
                if (size(min_heap) == k + 1) {
                    min_heap.pop();
                }
            }
            while (!empty(min_heap)) {
                const auto [v, i, j] = min_heap.top(); min_heap.pop();
                min_heaps[j].emplace(v, i, j);
                if (size(min_heaps[j]) == k + 1) {
                    min_heaps[j].pop();
                }
            }
        }
        priority_queue<Data, vector<Data>, greater<Data>> min_heap;
        for (auto& h : min_heaps) {
            while (!empty(h)) {
                const auto x = h.top(); h.pop();
                min_heap.emplace(x);
                if (size(min_heap) == ((k - 1) * (2 * k - 1) + 1) + 1) {  // each choice excludes at most 2k-1 candidates, we should have at least (k-1)*(2k-1)+1 candidates
                    min_heap.pop();
                }
            }
        }
        int64_t result = numeric_limits<int64_t>::min();
        vector<Data> candidates;
        while (!empty(min_heap)) {
            const auto x = min_heap.top(); min_heap.pop();
            candidates.emplace_back(x);
        }
        combinations(size(candidates), k, 
                     [&](const vector<int>& idxs) {
                        const auto& [x0, x1, x2] = candidates[idxs[0]];
                        const auto& [y0, y1, y2] = candidates[idxs[1]];
                        const auto& [z0, z1, z2] = candidates[idxs[2]];
                        if ((x1 != y1 && y1 != z1 && z1 != x1) &&
                            (x2 != y2 && y2 != z2 && z2 != x2)) {
                            result = max(result, static_cast<int64_t>(x0) + y0 + z0);
                        }
                     });
        return result;
    }

