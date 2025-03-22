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

    vector<vector<int>> seePeople(vector<vector<int>>& heights) {
        vector<vector<int>> result(size(heights), vector<int>(size(heights[0])));
        const auto& count = [](const auto& height, int i, vector<int> *stk, const auto& increase) {
            while (!empty(*stk) && height(stk->back()) < height(i)) {
                increase(stk->back()); stk->pop_back();
            }
            if (!empty(*stk)) {
                increase(stk->back());
            }
            if (!empty(*stk) && height(stk->back()) == height(i)) {
                stk->pop_back();
            }
            stk->emplace_back(i);
        };

        for (int i = 0; i < size(heights); ++i) {
            const auto& height = [&](int x) {
                return heights[i][x];
            };
            const auto& increase = [&](int x) {
                ++result[i][x];
            };
            vector<int> stk;
            for (int j = 0; j < size(heights[0]); ++j) {
                count(height, j, &stk, increase);
            }
        }
        for (int j = 0; j < size(heights[0]); ++j) {
            const auto& height = [&](int x) {
                return heights[x][j];
            };
            const auto& increase = [&](int x) {
                ++result[x][j];
            };
            vector<int> stk;
            for (int i = 0; i < size(heights); ++i) {
                count(height, i, &stk, increase);
            }
        }
        return result;
    }

