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

    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        vector<int> result;

        sort(envelopes.begin(), envelopes.end(),  // O(nlogn)
            [](const pair<int, int>& a, const pair<int, int>& b) {
                if (a.first == b.first) {
                    return a.second > b.second;
                }
                return a.first < b.first;
            });
        for (const auto& envelope : envelopes) {
            const auto target = envelope.second;
            auto it = lower_bound(result.begin(), result.end(), target);  // O(logk)
            if (it == result.end()) {
                result.emplace_back(target);
            } else {
                *it = target;
            }
        }

        return result.size();
    }

