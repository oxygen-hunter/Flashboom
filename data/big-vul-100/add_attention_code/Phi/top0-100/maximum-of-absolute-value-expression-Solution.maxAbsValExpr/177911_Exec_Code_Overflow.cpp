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

    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
        // 1. max(|arr1[i]-arr1[j]| + |arr2[i]-arr2[j]| + |i-j| for i > j)
        //    = max(|arr1[i]-arr1[j]| + |arr2[i]-arr2[j]| + |i-j| for j > i)
        // 2. for i > j:
        //        (|arr1[i]-arr1[j]| + |arr2[i]-arr2[j]| + |i-j|)
        //        >= c1*(arr1[i]-arr1[j]) + c2*(arr2[i]-arr2[j]) + i-j for c1 in (1, -1), c2 in (1, -1)
        //        = (c1*arr1[i]+c2*arr2[i]+i) - (c1*arr1[j]+c2*arr2[j]+j) for c1 in (1, -1), c2 in (1, -1)
        // 1 + 2 => max(|arr1[i]-arr1[j]| + |arr2[i]-arr2[j]| + |i-j| for i != j)
        //          = max((c1*arr1[i]+c2*arr2[i]+i) - (c1*arr1[j]+c2*arr2[j]+j)
        //                for c1 in (1, -1), c2 in (1, -1) for i > j)
        int result = 0;
        for (const auto& c1 : {1, -1}) {
            for (const auto& c2 : {1, -1}) {
                int min_prev = c1 * arr1[0] + c2 * arr2[0] + 0;
                for (int i = 1; i < arr1.size(); ++i) {
                    const auto& curr = c1 * arr1[i] + c2 * arr2[i] + i;
                    result = max(result, curr - min_prev);
                    min_prev = min(min_prev, curr);
                }
            }
        }
        return result;
    }

