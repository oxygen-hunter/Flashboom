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


    vector<int> recoverArray(vector<int>& nums) {    
        auto check = [&nums](int k, unordered_map<int, int> cnt, vector<int> *result) {
            for (const auto& x : nums) {
                if (cnt[x] == 0) {
                    continue;
                }
                if (cnt[x + 2 * k] == 0) {
                    return false;
                }
                --cnt[x];
                --cnt[x + 2 * k];
                result->emplace_back(x + k);
            }
            return true;
        };
        sort(begin(nums), end(nums));
        unordered_map<int, int> cnt;
        for (const auto& x : nums) {
            ++cnt[x];
        }
        for (int i = 1; i <= size(nums) / 2; ++i) {
            int k = nums[i] - nums[0];
            if (k == 0 || k % 2) {
                continue;
            }
            k /= 2;
            vector<int> result;
            if (check(k, cnt, &result)) {
                return result;
            }
        }
        return {};
    }


