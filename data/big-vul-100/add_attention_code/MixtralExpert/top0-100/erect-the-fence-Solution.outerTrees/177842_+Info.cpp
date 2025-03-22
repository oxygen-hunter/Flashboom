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


    vector<vector<int>> outerTrees(vector<vector<int>>& P) {
        // 3D cross product of OA and OB vectors, (i.e z-component of their "2D" cross product, but remember that it is not defined in "2D").
        // Returns a positive value, if OAB makes a counter-clockwise turn,
        // negative for clockwise turn, and zero if the points are collinear.
        const auto& cross = [](const vector<int>& O, const vector<int>& A, const vector<int>& B) {
            return (A[0] - O[0]) * (B[1] - O[1]) - (A[1] - O[1]) * (B[0] - O[0]);
        };

        // Returns a list of points on the convex hull in counter-clockwise order.
        // Note: the last point in the returned list is the same as the first one.
        size_t n = P.size(), k = 0;
        if (n <= 3) {
            return P;
        }
        vector<vector<int>> H(2*n);

        // Sort points lexicographically
        sort(P.begin(), P.end());

        // Build lower hull
        for (size_t i = 0; i < n; ++i) {
            while (k >= 2 && cross(H[k-2], H[k-1], P[i]) < 0) k--; // modified
            H[k++] = P[i];
        }

        // Build upper hull
        for (size_t i = n-1, t = k+1; i > 0; --i) {
            while (k >= t && cross(H[k-2], H[k-1], P[i-1]) < 0) k--; // modified
            H[k++] = P[i-1];
        }

        H.resize(--k);        
        if (H[1] == H[k - 1]) {  // modified
            H.resize(k / 2 + 1);
        }
        return H;
    }


