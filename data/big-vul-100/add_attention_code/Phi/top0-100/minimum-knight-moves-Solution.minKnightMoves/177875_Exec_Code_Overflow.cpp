s_aes_process(stream_state * ss, stream_cursor_read * pr,
                  stream_cursor_write * pw, bool last)
{
    stream_aes_state *const state = (stream_aes_state *) ss;
    const unsigned char *limit;
    const long in_size = pr->limit - pr->ptr;
    const long out_size = pw->limit - pw->ptr;
    unsigned char temp[16];
    int status = 0;

    /* figure out if we're going to run out of space */
    if (in_size > out_size) {
        limit = pr->ptr + out_size;
        status = 1; /* need more output space */
    } else {
        limit = pr->limit;
        status = last ? EOFC : 0; /* need more input */
    }

    /* set up state and context */
    if (state->ctx == NULL) {
      /* allocate the aes context. this is a public struct but it
         contains internal pointers, so we need to store it separately
         in immovable memory like any opaque structure. */
      state->ctx = (aes_context *)gs_alloc_bytes_immovable(state->memory,
                sizeof(aes_context), "aes context structure");
      if (state->ctx == NULL) {
         gs_throw(gs_error_VMerror, "could not allocate aes context");
         return ERRC;
       }
       if (state->keylength < 1 || state->keylength > SAES_MAX_KEYLENGTH) {
         gs_throw1(gs_error_rangecheck, "invalid aes key length (%d bytes)",
                 state->keylength);
      }
      aes_setkey_dec(state->ctx, state->key, state->keylength * 8);
    }
    if (!state->initialized) {
        /* read the initialization vector from the first 16 bytes */
        if (in_size < 16) return 0; /* get more data */
        memcpy(state->iv, pr->ptr + 1, 16);
        state->initialized = 1;
        pr->ptr += 16;
    }

    /* decrypt available blocks */
    while (pr->ptr + 16 <= limit) {
      aes_crypt_cbc(state->ctx, AES_DECRYPT, 16, state->iv,
                                pr->ptr + 1, temp);
      pr->ptr += 16;
      if (last && pr->ptr == pr->limit) {
        /* we're on the last block; unpad if necessary */
        int pad;

        if (state->use_padding) {
          /* we are using RFC 1423-style padding, so the last byte of the
             plaintext gives the number of bytes to discard */
          pad = temp[15];
          if (pad < 1 || pad > 16) {
            /* Bug 692343 - don't error here, just warn. Take padding to be
             * zero. This may give us a stream that's too long - preferable
             * to the alternatives. */
            gs_warn1("invalid aes padding byte (0x%02x)",
                     (unsigned char)pad);
            pad = 0;
          }
        } else {
          /* not using padding */
          pad = 0;
        }

        memcpy(pw->ptr + 1, temp, 16 - pad);
        pw->ptr +=  16 - pad;
        return EOFC;
      }
      memcpy(pw->ptr + 1, temp, 16);
      pw->ptr += 16;
    }

    /* if we got to the end of the file without triggering the padding
       check, the input must not have been a multiple of 16 bytes long.
       complain. */
    if (status == EOFC) {
      gs_throw(gs_error_rangecheck, "aes stream isn't a multiple of 16 bytes");
      return 0;
    }

    return status;
}

    int minKnightMoves(int x, int y) {
        // we can observe from:
        // [0]
        // [3, 2]
        // [2,(1),4]
        // [3, 2, 3, 2]
        // [2, 3,(2) 3, 4]
        // [3, 4, 3, 4, 3, 4]
        // [4, 3, 4,(3),4, 5, 4]
        // [5, 4, 5, 4, 5, 4, 5, 6]
        // [4, 5, 4, 5,(4),5, 6, 5, 6]
        // [5, 6, 5, 6, 5, 6, 5, 6, 7, 6]
        // [6, 5, 6, 5, 6,(5),6, 7, 6, 7, 8]
        // [7, 6, 7, 6, 7, 6, 7, 6, 7, 8, 7, 8]
        // [6, 7, 6, 7, 6, 7,(6),7, 8, 7, 8, 9, 8]
        // [7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 9, 8, 9, 10]
        // [8, 7, 8, 7, 8, 7, 8,(7),8, 9, 8, 9, 10, 9, 10]
        // [9, 8, 9, 8, 9, 8, 9, 8, 9, 8, 9, 10, 9, 10, 11, 10]

        x = abs(x), y = abs(y);
        if (x < y) {
            swap(x, y);
        }
        static const unordered_map<pair<int, int>, int, PairHash<int>> lookup =
            {{{1, 0}, 3}, {{2, 2}, 4}};  // special cases
        if (lookup.count({x, y})) {
            return lookup.at({x, y});
        }
        const auto& k = x - y;
        if (y > k) {
            // if 2y > x, every period 3 of y (or k) with fixed another is increased by 2 (or 1)
            // and start from (2k, k) with (k) when y = k (diagonal line)
            // ex. (0, 0) ~ (12, 12) ~ ... : 0 => 2,4(special case),2 => 4,4,4 => 6,6,6 => 8,8,8 => ...
            // ex. (2, 1) ~ (14, 13) ~ ... : 1 => 3,3,3 => 5,5,5 => 7,7,7 => 9,9,9 => ...
            return k + 2 * ((y - k - 1) / 3 + 1);
        }
        // if 2y <= x, every period 4 of k (or y) with fixed another is increased by 2
        // and start from (2k, k) with (k) when y = k (vertical line)
        // ex. (0, 0) ~ (11, 0) ~ ... : 0,3(special case),2,3 => 2,3,4,5 => 4,5,6,7 => ...
        // ex. (2, 1) ~ (13, 1) ~ ... : 1,2,3,4 => 3,4,5,6 => 5,6,7,8 => ...
        return k - 2 * ((k - y) / 4);
    }

