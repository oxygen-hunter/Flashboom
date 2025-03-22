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


    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        unordered_map<int, int> cnt1;
        for (const auto& x : nums) {
            ++cnt1[x];
        }
        vector<int64_t> cnt2(ranges::max(nums) + 1);
        for (int g = size(cnt2) - 1; g >= 1; --g) {
            int64_t c = 0;
            for (int ng = g; ng < size(cnt2); ng += g) {
                c += cnt1[ng];
            }
            cnt2[g] = c * (c - 1) / 2;
            for (int ng = g + g; ng < size(cnt2); ng += g) {
                cnt2[g] -= cnt2[ng];
            }
        }
        vector<int64_t> prefix(size(cnt2) + 1);
        for (int i = 0; i < size(prefix) - 1; ++i) {
            prefix[i + 1] += prefix[i] + cnt2[i];
        }
        vector<int> result(size(queries));
        for (int i = 0; i < size(queries); ++i) {
            result[i] = distance(cbegin(prefix), upper_bound(cbegin(prefix), cend(prefix), queries[i])) - 1;
        }
        return result;
    }


