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


    bool confusingNumber(int N) {
        static const unordered_map<char, char> lookup = 
            {{'0', '0'}, {'1', '1'}, {'6', '9'},
             {'8', '8'}, {'9', '6'}};
 
        const auto& S = to_string(N);
        for (int i = 0; i < S.length(); ++i) {
            if (!lookup.count(S[i])) {
                return false;
            }
        }
        for (int i = 0; i < (S.length() + 1) / 2; ++i) {
            if (S[i] != lookup.at(S[S.length() - 1 - i])) {
                return true;
            }
        }
        return false;
    }


