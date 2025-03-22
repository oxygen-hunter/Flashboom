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

    int countPairs(vector<int>& nums) {
        static const int L = 7;
        static const int K = 2;
        vector<int> POW10(L);
        POW10[0] = 1;
        for (int i = 0; i + 1 < L; ++i) {
            POW10[i+1] = POW10[i] * 10;
        }
        const auto& at_most = [&](int k, int x) {
            unordered_set<int> lookup = {x};
            vector<int> result = {x};
            for (int u = 0; k; --k) {
                for (int v = size(result); u < v; ++u) {
                    const int x = result[u];
                    for (int i = 0; i < L; ++i) {
                        const int a = x / POW10[i] % 10;
                        for (int j = i + 1; j < L; ++j) {
                            const int b = x / POW10[j] % 10;
                            if (a == b) {
                                continue;
                            }
                            const int y = x -a * (POW10[i] - POW10[j]) + b * (POW10[i] - POW10[j]);
                            if (lookup.count(y)) {
                                continue;
                            }
                            lookup.emplace(y);
                            result.emplace_back(y);
                        }
                    }
                }
            }
            return result;
        };

        int result = 0;
        unordered_map<int, int> cnt1;
        for (const auto& x : nums) {
            ++cnt1[x];
        }
        unordered_map<int, int> cnt2;
        for (const auto& [x, v] : cnt1) {
            result += cnt2[x] * v + v * (v - 1) / 2;
            for (const auto& x : at_most(K, x)) {
                if (!cnt1.count(x)) {
                    continue;
                }
                cnt2[x] += v;
            }
        }
        return result;
    }

