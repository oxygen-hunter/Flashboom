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

    vector<int> executeInstructions(int n, vector<int>& startPos, string s) {
        static const unordered_map<char, pair<int, int>> directions = {
            {'U', {-1, 0}}, {'R', {0, 1}}, {'D', {1, 0}}, {'L', {0, -1}}
        };

        int x0 = startPos[0], y0 = startPos[1];
        int x = 0, y = 0;
        vector<int> result(size(s));
        iota(rbegin(result), rend(result), 1);
        unordered_map<int, vector<int>> lookup_x, lookup_y;
        lookup_x[x0 - x].emplace_back(0);
        lookup_y[y0 - y].emplace_back(0);
        for (int i = 0; i < size(s); ++i) {
            const auto& [dx, dy] = directions.at(s[i]);
            x += dx, y += dy;
            for (const auto& k : {n - x, -x - 1}) {
                if (!lookup_x.count(k)) {
                    continue;
                }
                for (const auto& j : lookup_x[k]) {
                    result[j] = min(result[j], i - j);
                }
                lookup_x.erase(k);
            }
            for (const auto& k : {n - y, -y - 1}) {
                if (!lookup_y.count(k)) {
                    continue;
                }
                for (const auto& j : lookup_y[k]) {
                    result[j] = min(result[j], i - j);
                }
                lookup_y.erase(k);
            }
            lookup_x[x0 - x].emplace_back(i + 1);
            lookup_y[y0 - y].emplace_back(i + 1);
        }
        return result;
    }

