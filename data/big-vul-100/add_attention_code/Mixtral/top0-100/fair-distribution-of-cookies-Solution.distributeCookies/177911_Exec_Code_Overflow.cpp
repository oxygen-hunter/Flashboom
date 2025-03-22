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

    int distributeCookies(vector<int>& cookies, int k) {
        vector<int> total(1 << size(cookies));
        for (int mask = 0; mask < (1 << size(cookies)); ++mask) {
            for (int i = 0; i < size(cookies); ++i) {
                if (mask & (1 << i)) {
                    total[mask] += cookies[i];
                }
            }
        }
        vector<vector<int>> dp(2, vector<int>(1 << size(cookies), numeric_limits<int>::max()));
        dp[0][0] = 0;
        for (int i = 0; i < k; ++i) {
            for (int mask = 0; mask < (1 << size(cookies)); ++mask) {
                for (int submask = mask; submask; submask = (submask - 1) & mask) {
                    dp[(i + 1) % 2][mask] = min(dp[(i + 1) % 2][mask], max(total[submask], dp[i % 2][mask ^ submask]));
                }
            }
        }
        return dp[k % 2].back();
    }   

