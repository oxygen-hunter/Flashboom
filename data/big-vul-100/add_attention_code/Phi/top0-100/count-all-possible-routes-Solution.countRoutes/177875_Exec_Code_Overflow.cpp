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

    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        static const int MOD = 1e9 + 7;

        int s = locations[start];
        int f = locations[finish];
        sort(begin(locations), end(locations));
        start = distance(cbegin(locations), lower_bound(cbegin(locations), cend(locations), s));
        finish = distance(cbegin(locations), lower_bound(cbegin(locations), cend(locations), f));

        vector<vector<int>> left(locations.size(), vector<int>(fuel + 1));  // left[i][f], last move is toward left to location i by f fuel
        vector<vector<int>> right(locations.size(), vector<int>(fuel + 1));  // right[i][f], last move is toward right to location i by f fuel
        for (int f = 1; f <= fuel; ++f) {
            for (int j = 0; j < locations.size() - 1; ++j) {
                int d = locations[j + 1] - locations[j];
                if (f > d) {
                    // left[j][f] = right[j+1][f-d(j, j+1)] + 2*right[j+2][f-d(j, j+2)] + ... + 2^(k-1)*right[j+k][f-d(j, j+k)]
                    // => left[j+1][f] = (ight[j+2][f-d(j+1, j+2)] + 2*right[j+3][f-d(j+1, j+3)] + ... + 2^(k-2)*right[j+1+k-1][f-d(j+1, j+1+k-1)]
                    // => left[j+1][f-d(j, j+1)] = right[j+2][f-d(j, j+2)] + 2*right[j+3][f-d(j, j+3)] + ... + 2^(k-2)*right[j+k][f-d(j, j+k)]
                    // => left[j][f] = right[j+1][f-d(j, j+1)] + 2*left[j+1][f-d(j, j+1)]
                    left[j][f] = (right[j + 1][f - d] + 2 * left[j + 1][f - d] % MOD) % MOD;
                } else if (f == d) {
                    left[j][f] = int(j + 1 == start);
                }
            }
            for (int j = 1; j < locations.size(); ++j) {
                int d = locations[j] - locations[j - 1];
                if (f > d) {
                    // right[j][f] = left[j-1][f-d(j, j-1)] + 2*left[j-2][f-d(j, j-2)] + ... + 2^(k-1)*left[j-k][f-d(j, j-k)]
                    // => right[j-1][f] = left[j-2][f-d(j-1, j-2)] + 2*left[j-3][f-d(j-1, j-3)] + ... + 2^(k-2)*left[j-1-k+1][f-d(j-1, j-1-k+1)]
                    // => right[j-1][f-d(j, j-1)] = left[j-2][f-d(j, j-2)] + 2*left[j-3][f-d(j, j-3)] + ... + 2^(k-2)*left[j-k][f-d(j, j-k)]
                    // => right[j][f] = left[j-1][f-d(j, j-1)] + 2*right[j-1][f-d(j, j-1)]
                    right[j][f] = (left[j - 1][f - d] + 2 * right[j - 1][f - d] % MOD) % MOD;
                } else if (f == d) {
                    right[j][f] = int(j - 1 == start);
                }
            }
        }
        int result = int(start == finish);
        for (int f = 1; f <= fuel; ++f) {
            result = ((result + left[finish][f]) % MOD + right[finish][f]) % MOD;
        }
        return result;
    }

