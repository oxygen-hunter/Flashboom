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


    int minimumDistance(vector<vector<int>>& points) {
        const auto& max_distance = [&](int exclude) {
            static const int POS_INF = numeric_limits<int>::max();
            static const int NEG_INF = numeric_limits<int>::min();
    
            pair<int, int> max_sum = {NEG_INF, -1};
            pair<int, int> min_sum = {POS_INF, -1};
            pair<int, int> max_diff = {NEG_INF, -1};
            pair<int, int> min_diff = {POS_INF, -1};
            for (int i = 0; i < size(points); ++i) {
                if (i == exclude) {
                    continue;
                }
                const int x = points[i][0], y = points[i][1];
                max_sum = max(max_sum, {x + y, i});
                min_sum = min(min_sum, {x + y, i});
                max_diff = max(max_diff, {x - y, i});
                min_diff = min(min_diff, {x - y, i});
            }
            return max(tuple{max_sum.first - min_sum.first, max_sum.second, min_sum.second},
                       tuple{max_diff.first - min_diff.first, max_diff.second, min_diff.second});
        };
    
        const auto& [_, i, j] = max_distance(-1);
        return min(get<0>(max_distance(i)), get<0>(max_distance(j)));
    }


