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

    int minimumLines(vector<vector<int>>& points) {
        auto ceil_divide = [](int a, int b) {
            return (a + b - 1) / b;
        };
        unordered_map<tuple<int, int, int>, unordered_set<pair<int, int>, PairHash<int>>, TupleHash<int, int, int>> lookup;
        for (int i = 0; i < size(points); ++i) {
            const int x1 = points[i][0], y1 = points[i][1];
            for (int j = i + 1; j < size(points); ++j) {
                const int x2 = points[j][0], y2 = points[j][1];
                // (x-x1)/(x2-x1) = (y-y1)/(y2-y1)
                // => (y2-y1)x - (x2-x1)y = x1(y2-y1) - y1(x2-x1)
                int a = y2 - y1;
                int b = -(x2 - x1);
                int c = x1 * (y2 - y1) - y1 * (x2 - x1);
                const int g = gcd(gcd(a, b), c);
                a /= g, b /= g, c /= g;
                lookup[{a, b, c}].emplace(x1, y1);
                lookup[{a, b, c}].emplace(x2, y2);
            }
        }
        vector<tuple<int, int, int>> lines;
        for (const auto& [l, p] : lookup) {
            if (size(p) > 2) {  // filter to improve complexity
                lines.emplace_back(l);
            }
        }
        assert(size(lines) <= size(points) / 2);  // 1 extra colinear point per 2 points
        int result = numeric_limits<int>::max();
        const int mask_upper_bound = 1 << size(lines);
        for (int mask = 0; mask < mask_upper_bound; ++mask) {
            unordered_set<pair<int, int>, PairHash<int>> covered;
            for (int i = 0, bit = 1; bit <= mask; bit <<= 1, ++i) {
                if (mask & bit) {
                    for (const auto& x : lookup[lines[i]]) {
                        covered.emplace(x);
                    }
                }
            }
            result = min(result, __builtin_popcount(mask) + ceil_divide(size(points) - size(covered), 2));
        }
        return result;
    }

