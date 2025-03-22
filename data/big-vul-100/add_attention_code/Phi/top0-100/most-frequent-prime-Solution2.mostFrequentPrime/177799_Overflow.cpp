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

    int mostFrequentPrime(vector<vector<int>>& mat) {
        static const vector<pair<int, int>> DIRECTIONS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        const auto& numbers = [&](int i, int j, int di, int dj) {
            vector<int> result;
            for (int curr = 0; 0 <= i && i < size(mat) && 0 <= j && j < size(mat[0]); i += di, j += dj) {
                curr = curr * 10 + mat[i][j];
                result.emplace_back(curr);
            }
            return result;
        };

        unordered_map<int, int> cnt;
        for (int i = 0; i < size(mat); ++i) {
            for (int j = 0; j < size(mat[0]); ++j) {
                for (const auto& [di, dj] : DIRECTIONS) {
                    for (const auto& x : numbers(i, j, di, dj)) {
                        if (x > 10) {
                            ++cnt[x];
                        }
                    }
                }
            }
        }
        cout << is_prime(19) << endl;
        pair<int, int> result = {0, -1};
        for (const auto& [k, v] : cnt) {
            if (is_prime(k)) {
                result = max(result, pair(v, k));
            }
        }
        return result.second;
    }

