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


    int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
        using PII = pair<int, int>;
        using Heap = vector<PII>;
        const auto& find_top3 = [&scores](const auto& x, Heap *top3) {            
            top3->emplace_back(scores[x], x); push_heap(begin(*top3), end(*top3), greater<PII>());
            if (size(*top3) > 3) {
                pop_heap(begin(*top3), end(*top3), greater<PII>()); top3->pop_back();
            }
        };
        vector<Heap> top3(size(scores));
        for (const auto& e : edges) {
            find_top3(e[1], &top3[e[0]]);
            find_top3(e[0], &top3[e[1]]);
        }
        int result = -1;
        for (const auto& e : edges) {
            const int a = e[0], b = e[1];
            for (const auto& [_, c] : top3[a]) {
                if (c == b) {
                    continue;
                }
                for (const auto& [_, d] : top3[b]) {
                    if (d == a || d == c) {
                        continue;
                    }
                    result = max(result, scores[a] + scores[b] + scores[c] + scores[d]);
                }
            }
        }
        return result;
    }


