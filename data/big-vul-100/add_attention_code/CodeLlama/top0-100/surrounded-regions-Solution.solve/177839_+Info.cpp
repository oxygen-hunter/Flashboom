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


    void solve(vector<vector<char>>& board) {
        if (board.empty()) {
            return;
        }

        queue<pair<int, int>> q;
        for (int i = 0; i < board.size(); ++i) {
            if (board[i][0] == 'O') {
                board[i][0] = 'V';
                q.emplace(i, 0);
            }
            if (board[i][board[0].size() - 1] == 'O') {
                board[i][board[0].size() - 1] = 'V';
                q.emplace(i, board[0].size() - 1);
            }
        }

        for (int j = 1; j < board[0].size() - 1; ++j) {
            if (board[0][j] == 'O') {
                board[0][j] = 'V';
                q.emplace(0, j);
            }
            if (board[board.size() - 1][j] == 'O') {
                board[board.size() - 1][j] = 'V';
                q.emplace(board.size() - 1, j);
            }
        }
        while (!q.empty()) {
            int i, j;
            tie(i, j) = q.front();
            q.pop();
            static const vector<pair<int, int>> directions{{0, -1}, {0, 1},
                                                           {-1, 0}, {1, 0}};
            for (const auto& d : directions) {
                const int x = i + d.first, y = j + d.second;
                if (0 <= x && x < board.size() &&
                    0 <= y && y < board[0].size() &&
                    board[x][y] == 'O') {
                    board[x][y] = 'V';
                    q.emplace(x, y);
                }
            }
        }
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (board[i][j] != 'V') {
                    board[i][j] = 'X';
                } else {
                    board[i][j] = 'O';
                }
            }
        }
    }


