_PUBLIC_ codepoint_t next_codepoint_handle_ext(
			struct smb_iconv_handle *ic,
			const char *str, size_t len,
			charset_t src_charset,
			size_t *bytes_consumed)
{
	/* it cannot occupy more than 4 bytes in UTF16 format */
	uint8_t buf[4];
	smb_iconv_t descriptor;
	size_t ilen_orig;
	size_t ilen;
        size_t olen;
        char *outbuf;
 
       if ((str[0] & 0x80) == 0) {
                *bytes_consumed = 1;
                return (codepoint_t)str[0];
        }
	 * This is OK as we only support codepoints up to 1M (U+100000)
	 */
	ilen_orig = MIN(len, 5);
	ilen = ilen_orig;

	descriptor = get_conv_handle(ic, src_charset, CH_UTF16);
	if (descriptor == (smb_iconv_t)-1) {
		*bytes_consumed = 1;
		return INVALID_CODEPOINT;
	}

	/*
	 * this looks a little strange, but it is needed to cope with
	 * codepoints above 64k (U+1000) which are encoded as per RFC2781.
	 */
	olen = 2;
	outbuf = (char *)buf;
	smb_iconv(descriptor, &str, &ilen, &outbuf, &olen);
	if (olen == 2) {
		olen = 4;
		outbuf = (char *)buf;
		smb_iconv(descriptor,  &str, &ilen, &outbuf, &olen);
		if (olen == 4) {
			/* we didn't convert any bytes */
			*bytes_consumed = 1;
			return INVALID_CODEPOINT;
		}
		olen = 4 - olen;
	} else {
		olen = 2 - olen;
	}

	*bytes_consumed = ilen_orig - ilen;

	if (olen == 2) {
		return (codepoint_t)SVAL(buf, 0);
	}
	if (olen == 4) {
		/* decode a 4 byte UTF16 character manually */
		return (codepoint_t)0x10000 +
			(buf[2] | ((buf[3] & 0x3)<<8) |
			 (buf[0]<<10) | ((buf[1] & 0x3)<<18));
	}

	/* no other length is valid */
	return INVALID_CODEPOINT;
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


