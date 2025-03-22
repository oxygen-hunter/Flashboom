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


        int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
            const int m = obstacleGrid.size();
            const int n = obstacleGrid[0].size();
            vector<int> v(n, 0);

            v[0] = 1;
            for(int i = 0; i < m; ++i) {
                if(obstacleGrid[i][0] != 0)
                    v[0] = 0;
                for(int j = 1; j < n; ++j) {
                    if(obstacleGrid[i][j] == 0)
                        v[j] += v[j - 1];
                    else
                        v[j] = 0;
                }
            }

            return v[n - 1];
        }


