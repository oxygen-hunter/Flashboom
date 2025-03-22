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


    int getFood(vector<vector<char>>& grid) {
        static const vector<pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        vector<pair<int, int>> q;
        for (int r = 0; r < size(grid); ++r) {
            for (int c = 0; c < size(grid[0]); ++c) {
                if (grid[r][c] == '*') {
                    q.emplace_back(r, c);
                    break;
                }
            }
        }
        
        int result = 0;
        while (!empty(q)) {
            ++result;
            vector<pair<int, int>> new_q;
            for (const auto& [r, c] : q) {
                for (const auto& [dr, dc] : directions) {
                    int nr = r + dr, nc = c + dc;
                    if (!(0 <= nr && nr < size(grid) &&
                          0 <= nc && nc < size(grid[0]) &&
                          grid[nr][nc] != 'X')) {
                        continue;
                    }
                    if (grid[nr][nc] == '#') {
                        return result;
                    }
                    grid[nr][nc] = 'X';
                    new_q.emplace_back(nr, nc);
                }
            }
            q = move(new_q);
        }
        return -1;
    }


