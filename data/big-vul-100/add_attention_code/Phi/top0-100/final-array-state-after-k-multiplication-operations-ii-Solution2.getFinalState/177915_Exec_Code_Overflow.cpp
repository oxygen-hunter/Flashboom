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

    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        static const double EPS = 1e-15;
        static const int MOD = 1e9 + 7;
        const auto& powmod = [&](int a, int b) {
            a %= MOD;
            int64_t result = 1;
            while (b) {
                if (b & 1) {
                    result = result * a % MOD;
                }
                a = int64_t(a) * a % MOD;
                b >>= 1;
            }
            return result;
        };

        const auto& binary_search_right = [](auto left, auto right, const auto& check) {
            while (left <= right) {
                const auto mid = left + (right - left) / 2;
                if (!check(mid)) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return right;
        };

        const auto& count = [](const auto& x, int target) {
            return static_cast<int>(target - x + EPS);
        };

        if (multiplier == 1) {
            return nums;
        }
        using P = pair<double, int>;
        vector<P> vals;
        for (int i = 0; i < size(nums); ++i) {
            vals.emplace_back(log(nums[i]) / log(multiplier), i);
        }
        sort(begin(vals), end(vals));
        const auto& check = [&](const auto& target) {
            int result = 0;
            for (const auto& [x, i] : vals) {
                const int c = count(x, target);
                if (c <= 0) {
                    break;
                }
                result += c;
            }
            return result <= k;
        };

        const int target = binary_search_right(1, static_cast<int>(vals.back().first) + 1, check);
        vector<int64_t> nums2(cbegin(nums), cend(nums));
        for (int idx = 0; idx < size(vals); ++idx) {
            const auto& [x, i] = vals[idx];
            const int c = count(x, target);
            if (c <= 0) {
                break;
            }
            k -= c;
            nums2[i] *= pow(multiplier, c);
        }
        using P2 = pair<int64_t, int>;
        vector<P2> vals2;
        for (int i = 0; i < size(nums2); ++i) {
            vals2.emplace_back(nums2[i], i);
        }
        sort(begin(vals2), end(vals2));
        const int q = k / size(nums), r = k % size(nums);
        const int m = powmod(multiplier, q);
        vector<int> result(size(nums));
        for (int idx = 0; idx < size(vals2); ++idx) {
            const auto& [x, i] = vals2[idx];
            result[i] = ((x % MOD * m) % MOD * (idx < r ? multiplier : 1)) % MOD;
        }
        return result;
    }

