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


    bool hasValidPath(vector<vector<int>>& grid) {
        static const pair<int, int> E = {0,  1}, S = {1,  0},
                                    W = {0, -1}, N = {-1, 0};
        static const vector<vector<pair<int, int>>> directions = {
            {W, E}, {N, S},
            {W, S}, {S, E},
            {W, N}, {N, E}
        };

        for (auto [r, c] : directions.at(grid[0][0] - 1)) {
            if (!(0 <= r && r < grid.size() &&
                  0 <= c && c < grid[0].size())) {
                continue;
            }
            int pr = 0, pc = 0;
            while (r != grid.size() - 1 || c != grid[0].size() - 1) {
                bool is_found = false;
                for (const auto& [dx, dy] : directions.at(grid[r][c] - 1)) {
                    const auto& [nr, nc] = pair(r + dx, c + dy);
                    if ((nr == pr && nc == pc) ||
                        !(0 <= nr && nr < grid.size() &&
                          0 <= nc && nc < grid[0].size())) {
                        continue;
                    }
                    const auto& dirs = directions.at(grid[nr][nc] - 1);
                    if (find(cbegin(dirs), cend(dirs), pair(-dx, -dy)) == cend(dirs)) {
                        continue;
                    }
                    tie(pr, pc, r, c) = tuple(r, c, nr, nc);
                    is_found = true;
                    break;
                }
                if (!is_found) {
                    return false;
                }
            }
            return true;
        }
        return grid.size() == 1 && grid[0].size() == 1;
    }


