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


    int mergeStones(vector<int>& stones, int K) {
        if ((stones.size() - 1) % (K - 1)) {
            return -1;
        }
        vector<int> prefix(stones.size() + 1, 0);
        partial_sum(cbegin(stones), cend(stones), next(begin(prefix)), plus<int>());

        vector<vector<int> > dp(stones.size(), vector<int>(stones.size()));
        for (int l = K - 1; l < stones.size(); ++l) {
            for (int i = 0; i + l < stones.size(); ++i) {
                dp[i][i + l] = numeric_limits<int>::max();
                for (int j = i; j + 1 <= i + l; j += K - 1) {
                    dp[i][i + l] = min(dp[i][i + l], dp[i][j] + dp[j + 1][i + l]);
                }
                if (l % (K - 1) == 0) {
                    dp[i][i + l] += prefix[i + l + 1] - prefix[i];
                }
            }
        }
        return dp[0][stones.size() - 1];
    }


