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

    string fractionToDecimal(int numerator, int denominator) {
        string result;
        if ((numerator ^ denominator) >> 31 && numerator != 0) {
            result = "-";
        }

        auto dvd = llabs(numerator);
        auto dvs = llabs(denominator);
        result += to_string(dvd / dvs);
        dvd %= dvs;
        if (dvd > 0) {
            result += ".";
        }
        
        unordered_map<long long, int> lookup;
        while (dvd && !lookup.count(dvd)) {
            lookup[dvd] = result.length();
            dvd *= 10;
            result += to_string(dvd / dvs);
            dvd %= dvs;
        }

        if (lookup.count(dvd)) {
            result.insert(lookup[dvd], "(");
            result.push_back(')');
        }
        return result;
    }

