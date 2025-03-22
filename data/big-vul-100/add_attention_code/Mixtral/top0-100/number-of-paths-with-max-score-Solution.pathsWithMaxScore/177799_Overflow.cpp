_XcursorReadImage (XcursorFile		*file,
		   XcursorFileHeader	*fileHeader,
		   int			toc)
{
    XcursorChunkHeader	chunkHeader;
    XcursorImage	head;
    XcursorImage	*image;
    int			n;
    XcursorPixel	*p;

    if (!file || !fileHeader)
        return NULL;

    if (!_XcursorFileReadChunkHeader (file, fileHeader, toc, &chunkHeader))
	return NULL;
    if (!_XcursorReadUInt (file, &head.width))
	return NULL;
    if (!_XcursorReadUInt (file, &head.height))
	return NULL;
    if (!_XcursorReadUInt (file, &head.xhot))
	return NULL;
    if (!_XcursorReadUInt (file, &head.yhot))
	return NULL;
    if (!_XcursorReadUInt (file, &head.delay))
	return NULL;
    /* sanity check data */
    if (head.width >= 0x10000 || head.height > 0x10000)
	return NULL;
     if (!_XcursorReadUInt (file, &head.delay))
 	return NULL;
     /* sanity check data */
    if (head.width >= 0x10000 || head.height > 0x10000)
 	return NULL;
     if (head.width == 0 || head.height == 0)
 	return NULL;
	    return NULL;
    if (chunkHeader.version < image->version)
	image->version = chunkHeader.version;
    image->size = chunkHeader.subtype;
    image->xhot = head.xhot;
    image->yhot = head.yhot;
    image->delay = head.delay;
    n = image->width * image->height;
    p = image->pixels;
    while (n--)
    {
	if (!_XcursorReadUInt (file, p))
	{
	    XcursorImageDestroy (image);
	    return NULL;
	}
	p++;
    }
    return image;
}

    vector<int> pathsWithMaxScore(vector<string>& board) {
        static const int MOD = 1e9 + 7;
        static const vector<pair<int, int>> directions{{1, 0}, {0, 1}, {1, 1}};
        
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(board[0].size() + 1, vector<int>(2)));
        dp[(board.size() - 1) % 2][board[0].size() - 1] = {0, 1};
        for (int r = board.size() - 1; r >= 0; --r) {
            for (int c = board[0].size() - 1; c >= 0; --c) {
                if (board[r][c] == 'S' || board[r][c] == 'X') {
                    continue;
                }
                dp[r % 2][c] = {0, 0};
                for (const auto& [dr, dc] : directions) {
                    if (dp[r % 2][c][0] < dp[(r + dr) % 2][c + dc][0]) {
                        dp[r % 2][c] = dp[(r + dr) % 2][c + dc];
                    } else if (dp[r % 2][c][0] == dp[(r + dr) % 2][c + dc][0]) {
                        dp[r % 2][c][1] = (dp[r % 2][c][1]+dp[(r + dr) % 2][c + dc][1]) % MOD;
                    }
                }
                if (dp[r % 2][c][1] && board[r][c] != 'E') {
                    dp[r % 2][c][0] += board[r][c] - '0';
                }
            }
        }
        return dp[0][0];
    }

