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

    int minCostToEqualizeArray(vector<int>& nums, int cost1, int cost2) {
        static const int MOD = 1e9 + 7;

        const int n = size(nums);
        const int64_t mx = ranges::max(nums);
        int64_t total = mx * n - accumulate(cbegin(nums), cend(nums), 0ll);
        // fill until mx with only cost1 operations
        if (n <= 2 || 2 * cost1 <= cost2) {
            return total * cost1 % MOD;
        }

        int64_t result = numeric_limits<int64_t>::max();
        // fill until mx with more cost2 operations and fewer cost1 operations
        const int64_t mn = ranges::min(nums);
        int64_t cnt1 = max((mx - mn) - (total - (mx - mn)), static_cast<int64_t>(0));
        int64_t cnt2 = total - cnt1;
        result = min(result, (cnt1 + cnt2 % 2) * cost1 + cnt2 / 2 * cost2);

        // fill until mx+x with most cost2 operations and fewest cost1 operations,
        // where x is the max of x s.t. cnt1+x >= (n-1)*x => cnt1 >= (n-2)*x
        const int64_t x = cnt1 / (n - 2);
        cnt1 %= n - 2;
        total += n * x;
        cnt2 = total - cnt1;
        result = min(result, (cnt1 + cnt2 % 2) * cost1 + (cnt2 / 2) * cost2);

        // fill until mx+x+1 or mx+x+2 with nearly all cost2 operations and at most one cost1 operation
        for (int _ = 0; _ < 2; ++_) {  // increase twice is for odd n
            total += n;
            result = min(result, total % 2 * cost1 + total / 2 * cost2);
        }
        return result % MOD;
    }

