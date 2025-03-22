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


    int findInteger(int k, int digit1, int digit2) {
        static const int MAX_NUM_OF_DIGITS = 10;

        if (digit1 < digit2) {
            swap(digit1, digit2);
        }
        for (int l = 1, total = 2; l <= MAX_NUM_OF_DIGITS; ++l, total <<= 1) {
            for (int mask = 0; mask < total; ++mask) {
                int64_t curr = 0;
                for (int bit = total >> 1; bit; bit >>= 1) {
                    curr = curr * 10 + ((mask & bit) ? digit1 : digit2);
                }
                if (k < curr && curr <= numeric_limits<int>::max() && curr % k == 0) {
                    return curr;
                }
            }
        }
        return -1; 
    }


