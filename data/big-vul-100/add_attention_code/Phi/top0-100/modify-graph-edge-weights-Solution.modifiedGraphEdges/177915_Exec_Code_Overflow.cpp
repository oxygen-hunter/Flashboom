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

    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].emplace_back(e[1], e[2]);
            adj[e[1]].emplace_back(e[0], e[2]);
        }
        const auto& dijkstra = [&](int start, int x) {
            vector<int> best(size(adj), target + 1);
            best[start] = 0;
            priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>, greater<pair<int64_t, int>>> min_heap;
            min_heap.emplace(0, start);
            while (!empty(min_heap)) {
                const auto [curr, u] = min_heap.top(); min_heap.pop();
                if (curr > best[u]) {
                    continue;
                }
                for (auto [v, w] : adj[u]) {
                    if (w == -1) {
                        w = x;
                    }
                    if (best[v] - curr <= w) {
                        continue;
                    }
                    best[v] = curr + w;
                    min_heap.emplace(curr + w, v);
                }
            }
            return best;
        };

        const auto& left = dijkstra(source, 1);
        if (!(left[destination] <= target)) {
            return {};
        }
        const auto& right = dijkstra(destination, target + 1);
        if (!(right[source] >= target)) {
            return {};
        }
        for (auto& e : edges) {
            if (e[2] == -1) {
                e[2] = max({target - left[e[0]] - right[e[1]], target - left[e[1]] - right[e[0]], 1});
            }
        }
        return edges;
    }

