  cff_charset_load( CFF_Charset  charset,
                    FT_UInt      num_glyphs,
                    FT_Stream    stream,
                    FT_ULong     base_offset,
                    FT_ULong     offset,
                    FT_Bool      invert )
  {
    FT_Memory  memory = stream->memory;
    FT_Error   error  = CFF_Err_Ok;
    FT_UShort  glyph_sid;


    /* If the the offset is greater than 2, we have to parse the */
    /* charset table.                                            */
    if ( offset > 2 )
    {
      FT_UInt  j;


      charset->offset = base_offset + offset;

      /* Get the format of the table. */
      if ( FT_STREAM_SEEK( charset->offset ) ||
           FT_READ_BYTE( charset->format )   )
        goto Exit;

      /* Allocate memory for sids. */
      if ( FT_NEW_ARRAY( charset->sids, num_glyphs ) )
        goto Exit;

      /* assign the .notdef glyph */
      charset->sids[0] = 0;

      switch ( charset->format )
      {
      case 0:
        if ( num_glyphs > 0 )
        {
          if ( FT_FRAME_ENTER( ( num_glyphs - 1 ) * 2 ) )
             goto Exit;
 
           for ( j = 1; j < num_glyphs; j++ )
            charset->sids[j] = FT_GET_USHORT();
 
           FT_FRAME_EXIT();
         }
            /* Read the first glyph sid of the range. */
            if ( FT_READ_USHORT( glyph_sid ) )
              goto Exit;

            /* Read the number of glyphs in the range.  */
            if ( charset->format == 2 )
            {
              if ( FT_READ_USHORT( nleft ) )
                goto Exit;
            }
            else
            {
              if ( FT_READ_BYTE( nleft ) )
                goto Exit;
            }

            /* Fill in the range of sids -- `nleft + 1' glyphs. */
            for ( i = 0; j < num_glyphs && i <= nleft; i++, j++, glyph_sid++ )
              charset->sids[j] = glyph_sid;
          }
        }
        break;

      default:
        FT_ERROR(( "cff_charset_load: invalid table format!\n" ));
        error = CFF_Err_Invalid_File_Format;
                 goto Exit;
             }


    int countWinningSequences(string s) {
        static const int MOD = 1e9 + 7;
        static const unordered_map<char, int> lookup = {{'F', 0}, {'W', 1}, {'E', 2}};

        vector<unordered_map<int, int>> dp(3);
        for (int i = 0; i < size(s); ++i) {
            vector<unordered_map<int, int>> new_dp(3);
            const auto x = lookup.at(s[i]);
            for (int j = 0; j < 3; ++j) {
                const int diff = ((j - x + 1) % 3 + 3) % 3 - 1;
                if (i == 0) {
                    new_dp[j][diff] = 1;
                    continue;
                }
                for (int k = 0; k < 3; ++k) {
                    if (k == j) {
                        continue;
                    }
                    for (const auto& [v, c] : dp[k]) {
                        new_dp[j][v + diff] = (new_dp[j][v + diff] + c) % MOD;
                    }
                }
            }
            dp = move(new_dp);
        }
        int result = 0;
        for (int j = 0; j < 3; ++j) {
            for (const auto& [v, c] : dp[j]) {
                if (v >= 1) {
                    result = (result + c) % MOD;
                }
            }
        }
        return result;
    }


