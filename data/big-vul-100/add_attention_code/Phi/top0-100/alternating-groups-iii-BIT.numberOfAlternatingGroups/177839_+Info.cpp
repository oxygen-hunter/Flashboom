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

    vector<int> numberOfAlternatingGroups(vector<int>& colors, vector<vector<int>>& queries) {
        const int n = size(colors);
        set<int> bst;
        BIT bit1(n + 1), bit2(n + 1);
        const auto& update = [&](int i, int d) {
            if (d == +1) {
                bst.emplace(i);
                if (size(bst) == 1) {
                    bit1.add(n, +1);
                    bit2.add(n, +n);
                }
            }
            auto curr = bst.find(i);
            auto prv = prev(curr != begin(bst) ? curr : end(bst));
            auto nxt = next(curr);
            if (nxt == end(bst)) {
                nxt = begin(bst);
            }
            if (size(bst) != 1) {
                int l = ((*nxt) - (*prv) + (n - 1)) % n + 1;
                bit1.add(l, d * -1);
                bit2.add(l, d * -l);
                l = ((*curr) - (*prv) + n) % n;
                bit1.add(l, d * +1);
                bit2.add(l, d * +l);
                l = ((*nxt) - (*curr) + n) % n;
                bit1.add(l, d * +1);
                bit2.add(l, d * +l);
            }
            if (d == -1) {
                if (size(bst) == 1) {
                    bit1.add(n, -1);
                    bit2.add(n, -n);
                }
                bst.erase(curr);
            }
        };

        vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (colors[i] == colors[(i + 1) % n]) {
                update(i, +1);
            }
        }
        for (const auto &q : queries) {
            if (q[0] == 1) {
                const int l = q[1];
                result.emplace_back(!empty(bst) ? (bit2.query(n) - bit2.query(l - 1)) - 
                                                  (l - 1) * (bit1.query(n) - bit1.query(l - 1)) : n);
                continue;
            }
            const int i = q[1];
            if (colors[i] == q[2]) {
                continue;
            }
            colors[i] = q[2];
            update((i - 1 + n) % n, colors[i] == colors[(i - 1 + n) % n] ? +1 : -1);
            update(i, colors[i] == colors[(i + 1) % n] ? +1 : -1);
        }
        return result;
    }

