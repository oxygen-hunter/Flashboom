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

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        const auto& binary_search = [](int left, int right, const auto& check) {
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (check(mid)) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return left;
        };

        const auto& findKthInSortedArrays = [&](const auto& arrays, int k) {
            const auto& check = [&](int num) {
                int res = 0;
                for (const auto& arr : arrays) {
                    if (!empty(*arr)) {  // count the number of values which are less or equal to num
                        res += distance(cbegin(*arr), upper_bound(cbegin(*arr), cend(*arr), num));
                    }
                }
                return res >= k;
            };

            int left = numeric_limits<int>::max();
            int right = numeric_limits<int>::min();
            for (const auto arr : arrays) {
                if (!empty(*arr)) {
                    left = min(left, arr->front());
                    right = max(right, arr->back());
                }
            }
            return binary_search(left, right, check);
        };

        vector<vector<int> *> arrays{&nums1, &nums2};
        int total = accumulate(cbegin(arrays), cend(arrays), 0, [](const auto& x, const auto& y) {
            return x + size(*y);
        });
        if (total % 2 == 1) {
            return findKthInSortedArrays(arrays, total / 2 + 1);
        } else {
            return (findKthInSortedArrays(arrays, total / 2) +
                    findKthInSortedArrays(arrays, total / 2 + 1)) / 2.0;
        }
    }

