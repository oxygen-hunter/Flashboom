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

    int maxPointsInsideSquare(vector<vector<int>>& points, string s) {
        static const int INF = numeric_limits<int>::max();
    
        vector<int> lookup(26, INF);
        int d = INF;
        for (int i = 0; i < size(s); ++i) {
            int mn2 = max(abs(points[i][0]), abs(points[i][1]));
            if (mn2 < lookup[s[i] - 'a']) {
                swap(mn2, lookup[s[i] - 'a']);
            }
            d = min(d, mn2);
        }
        int result = 0;
        for (const auto& x : lookup) {
            if (x < d) {
                ++result;
            }
        }
        return result;
    }

