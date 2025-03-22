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


    int minimumTime(vector<vector<int>>& grid) {
        static const vector<pair<int, int>> DIRECTIONS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        if (min(grid[0][1], grid[1][0]) > 1) {
            return -1;
        }
        const auto& dijkstra = [&](const pair<int, int>& start, const pair<int, int>& target) {
            vector<vector<int>> best(size(grid), vector<int>(size(grid[0]), numeric_limits<int>::max()));
            best[start.first][start.second] = 0;
            using Data = tuple<int, int, int>;
            priority_queue<Data, vector<Data>, greater<Data>> min_heap;
            min_heap.emplace(0, start.first, start.second);
            while (!empty(min_heap)) {
                const auto [curr, i, j] = min_heap.top(); min_heap.pop();
                if (best[i][j] < curr) {
                    continue;
                }
                if (pair(i, j) == target) {
                    break;
                }
                for (const auto& [di, dj] : DIRECTIONS) {
                    const auto ni = i + di, nj = j + dj;
                    if (!(0 <= ni && ni < size(grid) &&
                          0 <= nj && nj < size(grid[0]) &&
                          best[ni][nj] > max(grid[ni][nj] + static_cast<int>(grid[ni][nj] % 2 == curr % 2), curr + 1))) {
                        continue;
                    }
                    best[ni][nj] = max(grid[ni][nj] + static_cast<int>(grid[ni][nj] % 2 == curr % 2), curr + 1);
                    min_heap.emplace(best[ni][nj], ni, nj);
                }
            }
            return best[target.first][target.second];
        };

        return dijkstra(pair(0, 0), pair(size(grid) - 1, size(grid[0]) - 1));
    }


