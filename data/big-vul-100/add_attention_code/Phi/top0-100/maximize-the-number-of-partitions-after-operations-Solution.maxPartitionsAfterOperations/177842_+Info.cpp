 _PUBLIC_ codepoint_t next_codepoint_handle_ext(
                        struct smb_iconv_handle *ic,
                       const char *str, charset_t src_charset,
                        size_t *bytes_consumed)
 {
        /* it cannot occupy more than 4 bytes in UTF16 format */
	smb_iconv_t descriptor;
	size_t ilen_orig;
	size_t ilen;
	size_t olen;
	char *outbuf;

	if ((str[0] & 0x80) == 0) {
		*bytes_consumed = 1;
		return (codepoint_t)str[0];
	}

	/*
	 * we assume that no multi-byte character can take more than 5 bytes.
         * we assume that no multi-byte character can take more than 5 bytes.
         * This is OK as we only support codepoints up to 1M (U+100000)
         */
       ilen_orig = strnlen(str, 5);
        ilen = ilen_orig;
 
        descriptor = get_conv_handle(ic, src_charset, CH_UTF16);
		*bytes_consumed = 1;
		return INVALID_CODEPOINT;
	}

    int maxPartitionsAfterOperations(string s, int k) {
        vector<int> left(size(s) + 1);
        vector<int> left_mask(size(s) + 1);
        for (int i = 0, cnt = 0, mask = 0; i < size(s); ++i) {
            mask |= 1 << (s[i] - 'a');
            if (__builtin_popcount(mask) > k) {
                ++cnt;
                mask = 1 << (s[i] - 'a');
            }
            left[i + 1] = cnt;
            left_mask[i + 1] = mask;
        }
        vector<int> right(size(s) + 1);
        vector<int> right_mask(size(s) + 1);
        for (int i = size(s) - 1, cnt = 0, mask = 0; i >= 0; --i) {
            mask |= 1 << (s[i] - 'a');
            if (__builtin_popcount(mask) > k) {
                ++cnt;
                mask = 1 << (s[i] - 'a');
            }
            right[i] = cnt;
            right_mask[i] = mask;
        }

        int result = 0;
        for (int i = 0; i < size(s); ++i) {
            int curr = left[i] + right[i + 1];
            const int mask = left_mask[i] | right_mask[i + 1];
            if (__builtin_popcount(left_mask[i]) == k && __builtin_popcount(right_mask[i + 1]) == k && __builtin_popcount(mask) != 26) {
                curr += 3;
            } else if (__builtin_popcount(mask) + (__builtin_popcount(mask) != 26 ? 1 : 0) > k) {  // test case: s = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", k = 26
                curr += 2;
            } else {
                curr += 1;
            }
            result = max(result, curr);
        }
        return result;
    }

