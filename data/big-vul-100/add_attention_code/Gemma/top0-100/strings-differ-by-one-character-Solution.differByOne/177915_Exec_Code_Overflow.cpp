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


    bool differByOne(vector<string>& dict) {
        static const int MOD = 1e9 + 7;
        static const int64_t P = 113;

        vector<int> hashes(dict.size());
        for (int i = 0; i < dict.size(); ++i) {
            for (const auto& c : dict[i]) {
                hashes[i] = (P * hashes[i] + (c - 'a')) % MOD;
            }
        }

        int64_t base = 1;
        for (int p = dict[0].length() - 1; p >= 0; --p) {
            unordered_map<int, vector<int>> lookup;
            for (int i = 0; i < dict.size(); ++i) {
                int new_hash = ((hashes[i] - base * (dict[i][p] - 'a') % MOD) + MOD) % MOD;
                if (lookup.count(new_hash)) {
                    auto target = dict[i].substr(0, p);
                    target += dict[i].substr(p + 1);
                    for (const auto& j : lookup[new_hash]) {
                        auto candidate = dict[j].substr(0, p);
                        candidate += dict[j].substr(p + 1);
                        if (candidate == target) {
                            return true;
                        }
                    }
                }
                lookup[new_hash].emplace_back(i);
            }
            base = (P * base) % MOD;
        }
        return false;
    }


