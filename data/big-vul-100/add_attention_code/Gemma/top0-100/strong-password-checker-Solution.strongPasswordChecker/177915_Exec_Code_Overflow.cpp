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


    int strongPasswordChecker(string s) {
        int missing_type_cnt = 3;
        missing_type_cnt -= static_cast<int>(any_of(s.begin(), s.end(), [](char c){ return isdigit(c); }));
        missing_type_cnt -= static_cast<int>(any_of(s.begin(), s.end(), [](char c){ return isupper(c); }));
        missing_type_cnt -= static_cast<int>(any_of(s.begin(), s.end(), [](char c){ return islower(c); }));

        int total_change_cnt = 0;
        int one_change_cnt = 0, two_change_cnt = 0, three_change_cnt = 0;
        for (int i = 2; i < s.length();) {
            if (s[i] == s[i - 1] && s[i - 1] == s[i - 2]) {
                int length = 2;
                while (i < s.length() && s[i] == s[i - 1]) {
                    ++length;
                    ++i;
                }
                total_change_cnt += length / 3;
                if (length % 3 == 0) {
                    ++one_change_cnt;
                } else if (length % 3 == 1) {
                    ++two_change_cnt;
                } else {
                    ++three_change_cnt;
                }
            } else {
                ++i;
            }
        }

        if (s.length() < 6) {
            return max(missing_type_cnt, 6 - static_cast<int>(s.length()));
        } else if (s.length() <= 20) {
            return max(missing_type_cnt, total_change_cnt);
        }

        int delete_cnt = s.length() - 20;
        
        total_change_cnt -= min(delete_cnt, one_change_cnt) / 1;
        total_change_cnt -= min(max(delete_cnt - one_change_cnt, 0), two_change_cnt * 2) / 2;
        total_change_cnt -= min(max(delete_cnt - one_change_cnt - 2 * two_change_cnt, 0), three_change_cnt * 3) / 3;
            
        return delete_cnt + max(missing_type_cnt, total_change_cnt);
    }


