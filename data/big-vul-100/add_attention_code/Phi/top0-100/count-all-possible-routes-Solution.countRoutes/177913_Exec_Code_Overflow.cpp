  tt_cmap8_validate( FT_Byte*      table,
                     FT_Validator  valid )
  {
    FT_Byte*   p = table + 4;
    FT_Byte*   is32;
    FT_UInt32  length;
    FT_UInt32  num_groups;


    if ( table + 16 + 8192 > valid->limit )
       FT_INVALID_TOO_SHORT;
 
     length = TT_NEXT_ULONG( p );
    if ( table + length > valid->limit || length < 8208 )
       FT_INVALID_TOO_SHORT;
 
     is32       = table + 12;
    p          = is32  + 8192;          /* skip `is32' array */
    num_groups = TT_NEXT_ULONG( p );

    if ( p + num_groups * 12 > valid->limit )
      FT_INVALID_TOO_SHORT;

    /* check groups, they must be in increasing order */
    {
      FT_UInt32  n, start, end, start_id, count, last = 0;


      for ( n = 0; n < num_groups; n++ )
      {
        FT_UInt   hi, lo;


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

          count = (FT_UInt32)( end - start + 1 );

          if ( start & ~0xFFFFU )
          {
            /* start_hi != 0; check that is32[i] is 1 for each i in */
            /* the `hi' and `lo' of the range [start..end]          */
            for ( ; count > 0; count--, start++ )
            {
              hi = (FT_UInt)( start >> 16 );
              lo = (FT_UInt)( start & 0xFFFFU );

              if ( (is32[hi >> 3] & ( 0x80 >> ( hi & 7 ) ) ) == 0 )
                FT_INVALID_DATA;

              if ( (is32[lo >> 3] & ( 0x80 >> ( lo & 7 ) ) ) == 0 )
                FT_INVALID_DATA;
            }
          }
          else
          {
            /* start_hi == 0; check that is32[i] is 0 for each i in */
            /* the range [start..end]                               */

            /* end_hi cannot be != 0! */
            if ( end & ~0xFFFFU )
              FT_INVALID_DATA;

            for ( ; count > 0; count--, start++ )
            {
              lo = (FT_UInt)( start & 0xFFFFU );

              if ( (is32[lo >> 3] & ( 0x80 >> ( lo & 7 ) ) ) != 0 )
                FT_INVALID_DATA;
            }
          }
        }

        last = end;
      }
    }

    return SFNT_Err_Ok;
  }

    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        static const int MOD = 1e9 + 7;

        int s = locations[start];
        int f = locations[finish];
        sort(begin(locations), end(locations));
        start = distance(cbegin(locations), lower_bound(cbegin(locations), cend(locations), s));
        finish = distance(cbegin(locations), lower_bound(cbegin(locations), cend(locations), f));

        vector<vector<int>> left(locations.size(), vector<int>(fuel + 1));  // left[i][f], last move is toward left to location i by f fuel
        vector<vector<int>> right(locations.size(), vector<int>(fuel + 1));  // right[i][f], last move is toward right to location i by f fuel
        for (int f = 1; f <= fuel; ++f) {
            for (int j = 0; j < locations.size() - 1; ++j) {
                int d = locations[j + 1] - locations[j];
                if (f > d) {
                    // left[j][f] = right[j+1][f-d(j, j+1)] + 2*right[j+2][f-d(j, j+2)] + ... + 2^(k-1)*right[j+k][f-d(j, j+k)]
                    // => left[j+1][f] = (ight[j+2][f-d(j+1, j+2)] + 2*right[j+3][f-d(j+1, j+3)] + ... + 2^(k-2)*right[j+1+k-1][f-d(j+1, j+1+k-1)]
                    // => left[j+1][f-d(j, j+1)] = right[j+2][f-d(j, j+2)] + 2*right[j+3][f-d(j, j+3)] + ... + 2^(k-2)*right[j+k][f-d(j, j+k)]
                    // => left[j][f] = right[j+1][f-d(j, j+1)] + 2*left[j+1][f-d(j, j+1)]
                    left[j][f] = (right[j + 1][f - d] + 2 * left[j + 1][f - d] % MOD) % MOD;
                } else if (f == d) {
                    left[j][f] = int(j + 1 == start);
                }
            }
            for (int j = 1; j < locations.size(); ++j) {
                int d = locations[j] - locations[j - 1];
                if (f > d) {
                    // right[j][f] = left[j-1][f-d(j, j-1)] + 2*left[j-2][f-d(j, j-2)] + ... + 2^(k-1)*left[j-k][f-d(j, j-k)]
                    // => right[j-1][f] = left[j-2][f-d(j-1, j-2)] + 2*left[j-3][f-d(j-1, j-3)] + ... + 2^(k-2)*left[j-1-k+1][f-d(j-1, j-1-k+1)]
                    // => right[j-1][f-d(j, j-1)] = left[j-2][f-d(j, j-2)] + 2*left[j-3][f-d(j, j-3)] + ... + 2^(k-2)*left[j-k][f-d(j, j-k)]
                    // => right[j][f] = left[j-1][f-d(j, j-1)] + 2*right[j-1][f-d(j, j-1)]
                    right[j][f] = (left[j - 1][f - d] + 2 * right[j - 1][f - d] % MOD) % MOD;
                } else if (f == d) {
                    right[j][f] = int(j - 1 == start);
                }
            }
        }
        int result = int(start == finish);
        for (int f = 1; f <= fuel; ++f) {
            result = ((result + left[finish][f]) % MOD + right[finish][f]) % MOD;
        }
        return result;
    }

