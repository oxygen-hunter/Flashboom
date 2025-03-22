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


    int minimumCost(int n, vector<vector<int>>& highways, int discounts) {
        using P = pair<int, int>;
        unordered_map<int, vector<P>> adj;
        for (const auto& highway : highways) {
            int u, v, w;
            tie(u, v, w) = make_tuple(highway[0], highway[1], highway[2]);
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        
        unordered_map<int, unordered_map<int, int>> best;
        best[0][discounts] = 0;
        using T = tuple<int, int, int>;
        priority_queue<T, vector<T>, greater<T>> min_heap;
        min_heap.emplace(0, 0, discounts);
        while (!empty(min_heap)) {
            auto [total, u, k] = min_heap.top(); min_heap.pop();
            if ((best.count(u) && best[u].count(k) &&  best[u][k] < total)) {
                continue;
            }
            if (u == n - 1) {
                return total;
            }
            for (const auto& [v, w] : adj[u]) {
                if (!best.count(v) ||
                    !best[v].count(k) ||
                    total + w < best[v][k]) {
                    best[v][k] = total + w;
                    min_heap.emplace(total + w, v, k);
                }
                if (k > 0 &&
                    (!best.count(v) ||
                    !best[v].count(k - 1) ||
                    total + w / 2 < best[v][k - 1])) {
                    best[v][k - 1] = total + w / 2;
                    min_heap.emplace(total + w / 2, v, k - 1);
                }
            }
        }
        return -1;
    }


