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


    int validSubarraySplit(vector<int>& nums) {
        static const int INF = numeric_limits<int>::max();

        vector<int> dp(size(nums) + 1, INF);  // dp[i]: min number of subarrays in nums[:i]
        dp[0] = 0;
        for (int i = 1; i <= size(nums); ++i) {
            for (int j = 0; j < i; ++j) {
                if (gcd(nums[j], nums[i - 1]) != 1) {
                    if (dp[j] != INF) {
                        dp[i] = min(dp[i], dp[j] + 1);
                    }
                }
            }
        }
        return dp.back() != INF ? dp.back() : -1;
    }


