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

    int distinctSequences(int n) {
        static const int MOD = 1e9 + 7;
        if (n == 1) {
            return 6;
        }
        vector<vector<int>> dp(6, vector<int>(6));
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                if (i != j && gcd(i + 1, j + 1) == 1) {
                    dp[i][j] = 1;
                }
            }
        }
        for (int _ = 0; _ < n - 2; ++_) {
            vector<vector<int>> new_dp(6, vector<int>(6));
            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 6; ++j) {
                    if (!dp[i][j]) {
                        continue;
                    }
                    for (int k = 0; k < 6; ++k) {
                        if (!dp[j][k]) {
                            continue;
                        }
                        if (k != i) {
                            new_dp[i][j] = (new_dp[i][j] + dp[j][k]) % MOD;
                        }
                    }
                }
            }
            dp = move(new_dp);
        }
        return accumulate(cbegin(dp), cend(dp), 0,
                          [&](int total, const auto& x) {
                              return (total + accumulate(cbegin(x), cend(x), 0,
                                                         [&](int total, int x) {
                                                             return (total + x) % MOD;
                                                         })) % MOD;
                          });
    }

