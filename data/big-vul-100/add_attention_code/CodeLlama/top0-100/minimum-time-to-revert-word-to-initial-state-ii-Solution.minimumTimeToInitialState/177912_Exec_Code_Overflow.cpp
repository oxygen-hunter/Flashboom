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


    int minimumTimeToInitialState(string word, int k) {
        const auto& ceil_divide = [](int a, int b) {
            return (a + b - 1) / b;
        };

        // Template: https://cp-algorithms.com/string/z-function.html
        const auto& z_function = [](const string& s) {  // Time: O(n), Space: O(n)
            vector<int> z(size(s));
            for (int i = 1, l = 0, r = 0; i < size(z); ++i) {
                if (i <= r) {
                    z[i] = min(r - i + 1, z[i - l]);
                }
                while (i + z[i] < size(z) && s[z[i]] == s[i + z[i]]) {
                    ++z[i];
                }
                if (i + z[i] - 1 > r) {
                    l = i, r = i + z[i] - 1;
                }
            }
            return z;
        };

        const auto& z = z_function(word);
        for (int i = k; i < size(word); i += k) {
            if (z[i] == size(word) - i) {
                return i / k;
            }
        }
        return ceil_divide(size(word), k);
    }


