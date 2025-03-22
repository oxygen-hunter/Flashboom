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


    int maxScore(vector<int>& nums) {
        vector<int> dp(1 << size(nums));
        for (int mask = 3; mask < size(dp); ++mask) {
            int cnt = __builtin_popcount(mask);
            if (cnt % 2) {
                continue;
            }
            vector<int> bits;
            for (int i = 0, m = mask; m; ++i, m >>= 1) {
                if (m & 1) {
                    bits.emplace_back(i);
                }
            }
            for (int i = 0; i < size(bits); ++i) {
                for (int j = i + 1; j < size(bits); ++j) {
                    dp[mask] = max(dp[mask], cnt / 2 * gcd(nums[bits[i]], nums[bits[j]]) + dp[mask ^ (1 << bits[i]) ^ (1 << bits[j])]);
                }
            }
        }
        return dp.back();
    }


