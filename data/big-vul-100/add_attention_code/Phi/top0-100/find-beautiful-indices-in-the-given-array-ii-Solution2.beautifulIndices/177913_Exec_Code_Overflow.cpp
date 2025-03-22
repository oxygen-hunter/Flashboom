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

    vector<int> beautifulIndices(string s, string a, string b, int k) {
        const auto& KMP = [&](const string& text, const string& pattern) {
            const auto& getPrefix = [&](const string& pattern) {
                vector<int> prefix(pattern.length(), -1);
                int j = -1;
                for (int i = 1; i < pattern.length(); ++i) {
                    while (j > -1 && pattern[j + 1] != pattern[i]) {
                        j = prefix[j];
                    }
                    if (pattern[j + 1] == pattern[i]) {
                        ++j;
                    }
                    prefix[i] = j;
                }
                return prefix;
            };

            vector<int> result;
            const vector<int> prefix = getPrefix(pattern + '#' + text);
            for (int i = (size(pattern) + 1) + (size(pattern) - 1); i < size(prefix); ++i) {
                if (prefix[i] + 1 == size(pattern)) {
                    result.emplace_back((i - (size(pattern) + 1)) - (size(pattern) - 1));
                }
            }
            return result;
        };

        vector<int> result;
        if (!(size(a) <= size(s) && size(b) <= size(s))) {
            return result;
        }
        const auto& lookup = KMP(s, b);
        int j = 0;
        for (const auto& i : KMP(s, a)) {
            const int j = distance(cbegin(lookup), lower_bound(cbegin(lookup), cend(lookup), i - k));
            if (j < size(lookup) && lookup[j] <= i + k) {
                result.emplace_back(i);
            }
        }
        return result;
    }

