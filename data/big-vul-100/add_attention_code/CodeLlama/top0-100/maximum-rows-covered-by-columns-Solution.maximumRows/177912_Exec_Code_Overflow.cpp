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


    int maximumRows(vector<vector<int>>& matrix, int numSelect) {
        const auto& next_popcount = [](uint32_t n) {  // reference: https://massivealgorithms.blogspot.com/2014/06/hakmem-item-175.html
            const uint32_t lowest_bit = n & -n;
            const uint32_t left_bits = n + lowest_bit;
            const uint32_t changed_bits = n ^ left_bits;
            const uint32_t right_bits = (changed_bits / lowest_bit) >> 2;
            return left_bits | right_bits;
        };

        vector<uint32_t> masks(size(matrix));
        for (int r = 0; r < size(matrix); ++r) {
            uint32_t m = 0;
            for (int c = 0; c < size(matrix[0]); ++c) {
                m |= matrix[r][c] << ((size(matrix[0]) - 1) - c);
            }
            masks[r] = m;
        }
        int result = 0;
        for (uint32_t mask = (1 << numSelect) - 1; mask < 1 << size(matrix[0]); mask = next_popcount(mask)) {
            const int cnt = accumulate(cbegin(masks), cend(masks), 0, [&](const auto& total, const auto& x) {
                return total + static_cast<int>((x & mask) == x);
            });
            result = max(result, cnt);
        }
        return result;
    }


