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

    long long maximumValueSum(vector<vector<int>>& board) {
        static const int k = 3;
    
        const auto& combinations = [](int n, int k, const auto& callback) {
            static const auto& next_pos =
                [](const auto& n, const auto& k, const auto& idxs) {
                    int i = k - 1;
                    for (; i >= 0; --i) {
                        if (idxs[i] != i + n - k) {
                            break;
                        }
                    }
                    return i;
                };
        
            vector<int> idxs(k);
            iota(begin(idxs), end(idxs), 0);
            callback(idxs);
            for (int i; (i = next_pos(n, k, idxs)) >= 0;) {
                ++idxs[i];
                for (int j = i + 1; j < k; ++j) {
                    idxs[j] = idxs[j - 1] + 1;
                }
                callback(idxs);
            }
        };
    
        using Data = tuple<int, int, int>;
        vector<priority_queue<Data, vector<Data>, greater<Data>>> min_heaps(size(board[0]));
        for (int i = 0; i < size(board); ++i) {
            priority_queue<Data, vector<Data>, greater<Data>> min_heap;
            for (int j = 0; j < size(board[0]); ++j) {
                min_heap.emplace(board[i][j], i, j);
                if (size(min_heap) == k + 1) {
                    min_heap.pop();
                }
            }
            while (!empty(min_heap)) {
                const auto [v, i, j] = min_heap.top(); min_heap.pop();
                min_heaps[j].emplace(v, i, j);
                if (size(min_heaps[j]) == k + 1) {
                    min_heaps[j].pop();
                }
            }
        }
        priority_queue<Data, vector<Data>, greater<Data>> min_heap;
        for (auto& h : min_heaps) {
            while (!empty(h)) {
                const auto x = h.top(); h.pop();
                min_heap.emplace(x);
                if (size(min_heap) == ((k - 1) * (2 * k - 1) + 1) + 1) {  // each choice excludes at most 2k-1 candidates, we should have at least (k-1)*(2k-1)+1 candidates
                    min_heap.pop();
                }
            }
        }
        int64_t result = numeric_limits<int64_t>::min();
        vector<Data> candidates;
        while (!empty(min_heap)) {
            const auto x = min_heap.top(); min_heap.pop();
            candidates.emplace_back(x);
        }
        combinations(size(candidates), k, 
                     [&](const vector<int>& idxs) {
                        const auto& [x0, x1, x2] = candidates[idxs[0]];
                        const auto& [y0, y1, y2] = candidates[idxs[1]];
                        const auto& [z0, z1, z2] = candidates[idxs[2]];
                        if ((x1 != y1 && y1 != z1 && z1 != x1) &&
                            (x2 != y2 && y2 != z2 && z2 != x2)) {
                            result = max(result, static_cast<int64_t>(x0) + y0 + z0);
                        }
                     });
        return result;
    }

