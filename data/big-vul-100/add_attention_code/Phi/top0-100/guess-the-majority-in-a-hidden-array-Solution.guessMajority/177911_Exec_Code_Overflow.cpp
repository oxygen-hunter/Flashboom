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

    int guessMajority(ArrayReader &reader) {
        int count_a = 1, count_b = 0, idx_b = -1;
        const auto& value_0_1_2_3 = reader.query(0, 1, 2, 3);
        int value_0_1_2_i = -1;
        for (int i = reader.length() - 1; i >= 4; --i) {
            value_0_1_2_i = reader.query(0, 1, 2, i);
            if (value_0_1_2_i == value_0_1_2_3) {  // nums[i] == nums[3]
                ++count_a;
            } else {
                ++count_b;
                idx_b = i;
            }
        }
        const auto& value_0_1_2_4 = value_0_1_2_i;
        for (int i = 0; i < 3; ++i) {
            vector<int> a_b;
            for (int j = 0; j < 3; ++j) {
                if (j == i) {
                    continue;
                }
                a_b.emplace_back(j);
            }
            const auto& value_a_b_3_4 = reader.query(a_b[0], a_b[1], 3, 4);
            if (value_a_b_3_4 == value_0_1_2_4) {  // nums[i] == nums[3]
                ++count_a;
            } else {
                ++count_b;
                idx_b = i;
            }
        }
        if (count_a == count_b) {
            return -1;
        }
        return count_a > count_b ? 3 : idx_b;
    }

