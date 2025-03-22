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

    vector<int> timeTaken(vector<vector<int>>& edges) {
        vector<vector<int>> adj(size(edges) + 1);
        for (const auto& e : edges) {
            adj[e[0]].emplace_back(e[1]);
            adj[e[1]].emplace_back(e[0]);
        }
        vector<vector<pair<int, int>>> dp(size(edges) + 1, vector<pair<int, int>>(2, pair(0, -1)));
        const function<void (int, int)> dfs1 = [&](int u, int p) {
            for (const auto& v : adj[u]) {
                if (v == p) {
                    continue;
                }
                dfs1(v, u);
                pair<int, int> curr = pair((v % 2 ? 1 : 2) + dp[v][0].first, v);
                for (int i = 0; i < size(dp[u]); ++i) {
                    if (curr > dp[u][i]) {
                        swap(curr, dp[u][i]);
                    }
              }
            }
        };

        vector<int> result(size(edges) + 1);
        const function<void (int, int, int)> dfs2 = [&](int u, int p, int curr) {
            result[u] = max(dp[u][0].first, curr);
            for (const auto& v : adj[u]) {
                if (v == p) {
                    continue;
                }
                dfs2(v, u, (u % 2 ? 1 : 2) + max(dp[u][dp[u][0].second == v].first, curr));
            }
        };
    
        dfs1(0, -1);
        dfs2(0, -1, 0);
        return result;
    }

