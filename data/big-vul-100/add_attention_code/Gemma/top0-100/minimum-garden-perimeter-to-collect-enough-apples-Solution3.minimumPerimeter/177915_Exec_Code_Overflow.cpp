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


    long long minimumPerimeter(long long neededApples) {
        // 2r  , 2r-1, ..., r+1, r  , r+1, ..., 2*r-1, 2*r
        // 2r-1,                 r-1,                  2r-1
        // .                     .                     .    
        // .                     .                     .    
        // .                     .                     .    
        // r+1 ,    r, ...,   2, 1  ,   2, ...,   r  , r+1
        // r   ,  r-1, ...,   1, 0  ,   1, ...,   r-1, r
        // r+1 ,    r, ...,   2, 1  ,   2, ...,   r  , r+1
        // .                     .                     .    
        // .                     .                     .    
        // .                     .                     .    
        // 2r-1,                 r-1,                  2r-1
        // 2r  , 2r-1, ..., r+1, r  , r+1, ..., 2*r-1, 2*r
        //
        // the sum of each row/col forms an arithmetic sequence
        // => let ai = (((r + (r-1) + ... + r + 0) + (0 + 1 + 2 + ... + r)) - 0) + i*(2r+1)
        //           = (2*(0+r)*(r+1)/2-0) + i*(2r+1)
        //           = r*(r+1) + i*(2r+1)
        // => total  = 2*(a0 + a1 + ... ar) - a0
        //           = 2*(r*(r+1) + r*(r+1) + r*(2r+1)))*(r+1)/2 - r*(r+1)
        //           = r*(4r+3)*(r+1)-r*(r+1)
        //           = 4r^3+6r^2+2r
        // => find min r, s.t. 4r^3+6r^2+2r >= neededApples

        int64_t left = 1, right = pow(neededApples / 4.0, 1.0 / 3);
        while (left <= right) {
            const auto& mid = left + (right - left) / 2;
            if (check(neededApples, mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return 8 * left;
    }


