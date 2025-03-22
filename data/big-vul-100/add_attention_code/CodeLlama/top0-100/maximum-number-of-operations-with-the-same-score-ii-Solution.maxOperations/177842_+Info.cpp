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


    int maxOperations(vector<int>& nums) {
        const function<int (int, int, int, vector<vector<int>>&)> memoization = [&](int left, int right, int target, vector<vector<int>>& lookup) {
            if (!(right - left + 1 >= 2)) {
                return 0;
            }
            if (lookup[left][right] == -1) {
                lookup[left][right] = max({nums[left] + nums[left + 1]   == target ? 1 + memoization(left + 2, right - 0, target, lookup) : 0,
                                           nums[left] + nums[right]      == target ? 1 + memoization(left + 1, right - 1, target, lookup) : 0,
                                           nums[right - 1] + nums[right] == target ? 1 + memoization(left + 0, right - 2, target, lookup) : 0});
            }
            return lookup[left][right];
        };

        int result = 0;
        for (const auto& target : unordered_set<int>{nums[0] + nums[1], nums[0] + nums[size(nums) - 1], nums[size(nums) - 2] + nums[size(nums) - 1]}) {
            vector<vector<int>> lookup(size(nums), vector<int>(size(nums), -1));
            result = max(result, memoization(0, size(nums) - 1, target, lookup));
        }
        return result;
    }


