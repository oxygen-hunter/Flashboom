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


    vector<int> cheapestJump(vector<int>& A, int B) {
        vector<int> result;
        if (A.empty() || A.back() == -1) {
            return result;
        }
        const int n = A.size();
        vector<int> dp(n, numeric_limits<int>::max()), next(n, -1);
        dp[n - 1] = A[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            if (A[i] == -1) {
                continue;
            }
            for (int j = i + 1; j <= min(i + B, n - 1); ++j) {
                if (dp[j] == numeric_limits<int>::max()) {
                    continue;
                }
                if (A[i] + dp[j] < dp[i]) {
                    dp[i] = A[i] + dp[j];
                    next[i] = j;
                }
            }
        }
        if (dp[0] == numeric_limits<int>::max()) {
            return result;
        }
        int k = 0;
        while (k != -1) {
            result.emplace_back(k + 1);
            k = next[k];
        }
        return result;
    }


