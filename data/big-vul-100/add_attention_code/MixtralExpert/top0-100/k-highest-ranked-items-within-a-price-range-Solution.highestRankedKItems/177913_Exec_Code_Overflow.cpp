  tt_cmap8_validate( FT_Byte*      table,
                     FT_Validator  valid )
  {
    FT_Byte*   p = table + 4;
    FT_Byte*   is32;
    FT_UInt32  length;
    FT_UInt32  num_groups;


    if ( table + 16 + 8192 > valid->limit )
       FT_INVALID_TOO_SHORT;
 
     length = TT_NEXT_ULONG( p );
    if ( table + length > valid->limit || length < 8208 )
       FT_INVALID_TOO_SHORT;
 
     is32       = table + 12;
    p          = is32  + 8192;          /* skip `is32' array */
    num_groups = TT_NEXT_ULONG( p );

    if ( p + num_groups * 12 > valid->limit )
      FT_INVALID_TOO_SHORT;

    /* check groups, they must be in increasing order */
    {
      FT_UInt32  n, start, end, start_id, count, last = 0;


      for ( n = 0; n < num_groups; n++ )
      {
        FT_UInt   hi, lo;


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

          count = (FT_UInt32)( end - start + 1 );

          if ( start & ~0xFFFFU )
          {
            /* start_hi != 0; check that is32[i] is 1 for each i in */
            /* the `hi' and `lo' of the range [start..end]          */
            for ( ; count > 0; count--, start++ )
            {
              hi = (FT_UInt)( start >> 16 );
              lo = (FT_UInt)( start & 0xFFFFU );

              if ( (is32[hi >> 3] & ( 0x80 >> ( hi & 7 ) ) ) == 0 )
                FT_INVALID_DATA;

              if ( (is32[lo >> 3] & ( 0x80 >> ( lo & 7 ) ) ) == 0 )
                FT_INVALID_DATA;
            }
          }
          else
          {
            /* start_hi == 0; check that is32[i] is 0 for each i in */
            /* the range [start..end]                               */

            /* end_hi cannot be != 0! */
            if ( end & ~0xFFFFU )
              FT_INVALID_DATA;

            for ( ; count > 0; count--, start++ )
            {
              lo = (FT_UInt)( start & 0xFFFFU );

              if ( (is32[lo >> 3] & ( 0x80 >> ( lo & 7 ) ) ) != 0 )
                FT_INVALID_DATA;
            }
          }
        }

        last = end;
      }
    }

    return SFNT_Err_Ok;
  }


    vector<vector<int>> highestRankedKItems(vector<vector<int>>& grid, vector<int>& pricing, vector<int>& start, int k) {
        static const vector<pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        vector<pair<int, int>> q = {{start[0], start[1]}};
        vector<vector<int>> lookup(size(grid), vector<int>(size(grid[0]), -1));
        int d = lookup[start[0]][start[1]] = 0;
        auto compare = [&](const auto& x, const auto& y) {
            return make_tuple(lookup[x[0]][x[1]], grid[x[0]][x[1]], x[0], x[1]) <
                   make_tuple(lookup[y[0]][y[1]], grid[y[0]][y[1]], y[0], y[1]);
        };
        vector<vector<int>> result;
        while (!empty(q)) {
            if (size(result) >= k) {
                if (size(result) > k) {
                    nth_element(begin(result), begin(result) + k, end(result), compare);
                    result.resize(k);
                }
                break;
            }
            vector<pair<int, int>> new_q;
            for (const auto& [r, c] : q) {
                if (pricing[0] <= grid[r][c] && grid[r][c] <= pricing[1]) {
                    result.push_back({r, c});
                }
                for (const auto& [dr, dc] : directions) {
                    const int nr = r + dr, nc = c + dc;
                    if (!((0 <= nr && nr < size(grid)) && (0 <= nc && nc < size(grid[0])) &&
                           grid[nr][nc] && lookup[nr][nc] == -1)) {
                        continue;
                    }
                    lookup[nr][nc] = d + 1;
                    new_q.emplace_back(nr, nc);
                }
            }
            q = move(new_q);
            ++d;
        }
        sort(begin(result), end(result), compare);
        return result;
    }


