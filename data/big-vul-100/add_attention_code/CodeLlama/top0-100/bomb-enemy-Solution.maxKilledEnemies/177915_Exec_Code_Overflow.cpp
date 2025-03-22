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


    int maxKilledEnemies(vector<vector<char>>& grid) {
        int result = 0;
        if (grid.empty() || grid[0].empty()) {
            return result;
        }

        vector<vector<int>> down{grid.size(), vector<int>(grid[0].size())};
        vector<vector<int>> right{grid.size(), vector<int>(grid[0].size())};
        for (int i = grid.size() - 1; i >= 0; --i) {
            for (int j = grid[0].size() - 1; j >= 0; --j) {
                if (grid[i][j] != 'W') {
                    if (i + 1 < grid.size()) {
                        down[i][j] = down[i + 1][j];
                    }
                    if (j + 1 < grid[0].size()) {
                        right[i][j] = right[i][j + 1];
                    }
                    if (grid[i][j] == 'E') {
                        ++down[i][j];
                        ++right[i][j];
                    }
                }
            }
        }

        int left = 0;
        vector<int> up(grid[0].size());
        for (int i = 0; i < grid.size(); ++i) {
            left = 0;
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == 'W') {
                    up[j] = 0;
                    left = 0;
                } else if (grid[i][j] == 'E') {
                    ++up[j];
                    ++left;
                } else {
                    result = max(result, left + up[j] + right[i][j] + down[i][j]);
                }
            }
        }

        return result;
    }


