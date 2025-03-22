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

    vector<int> solve(vector<int>& nums, vector<vector<int>>& queries) {
        static const int MOD = 1e9 + 7;
        
        vector<vector<vector<int>>> prefix(floor(sqrt(size(queries))) + 1, vector<vector<int>>(floor(sqrt(size(queries))) + 1));
        vector<int> result;
        for (const auto& query : queries) {
            int x = query[0], y = query[1];
            if (uint64_t(y) * y > size(queries)) {
                int total = 0;
                for (int i = x; i < size(nums); i += y) {
                    total = (total + nums[i]) % MOD;
                }
                result.emplace_back(total);
            } else {
                int begin = x % y;
                if (empty(prefix[begin][y])) {
                    prefix[begin][y].emplace_back(0);
                    for (int i = begin; i < size(nums); i += y) {
                        prefix[begin][y].emplace_back((prefix[begin][y].back() + nums[i]) % MOD);
                    }
                }
                result.emplace_back((prefix[begin][y].back() - prefix[begin][y][x / y] + MOD) % MOD);
            }
        }
        return result;
    }

