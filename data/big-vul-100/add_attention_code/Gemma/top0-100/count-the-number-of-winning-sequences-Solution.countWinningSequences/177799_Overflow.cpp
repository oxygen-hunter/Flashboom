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


    int countWinningSequences(string s) {
        static const int MOD = 1e9 + 7;
        static const unordered_map<char, int> lookup = {{'F', 0}, {'W', 1}, {'E', 2}};

        vector<unordered_map<int, int>> dp(3);
        for (int i = 0; i < size(s); ++i) {
            vector<unordered_map<int, int>> new_dp(3);
            const auto x = lookup.at(s[i]);
            for (int j = 0; j < 3; ++j) {
                const int diff = ((j - x + 1) % 3 + 3) % 3 - 1;
                if (i == 0) {
                    new_dp[j][diff] = 1;
                    continue;
                }
                for (int k = 0; k < 3; ++k) {
                    if (k == j) {
                        continue;
                    }
                    for (const auto& [v, c] : dp[k]) {
                        new_dp[j][v + diff] = (new_dp[j][v + diff] + c) % MOD;
                    }
                }
            }
            dp = move(new_dp);
        }
        int result = 0;
        for (int j = 0; j < 3; ++j) {
            for (const auto& [v, c] : dp[j]) {
                if (v >= 1) {
                    result = (result + c) % MOD;
                }
            }
        }
        return result;
    }


