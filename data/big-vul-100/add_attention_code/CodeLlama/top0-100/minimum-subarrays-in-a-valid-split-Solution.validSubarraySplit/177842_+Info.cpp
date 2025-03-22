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


    int validSubarraySplit(vector<int>& nums) {
        static const int INF = numeric_limits<int>::max();

        vector<int> dp(size(nums) + 1, INF);  // dp[i]: min number of subarrays in nums[:i]
        dp[0] = 0;
        for (int i = 1; i <= size(nums); ++i) {
            for (int j = 0; j < i; ++j) {
                if (gcd(nums[j], nums[i - 1]) != 1) {
                    if (dp[j] != INF) {
                        dp[i] = min(dp[i], dp[j] + 1);
                    }
                }
            }
        }
        return dp.back() != INF ? dp.back() : -1;
    }


