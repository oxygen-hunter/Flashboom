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


    int maxKilledEnemies(vector<vector<char>>& grid) {
        int result = 0;
        if (grid.empty() || grid[0].empty()) {
            return result;
        }

        vector<vector<int>> down{grid.size(), vector<int>(grid[0].size())};
        vector<vector<int>> right{grid.size(), vector<int>(grid[0].size())};
        for (int i = grid.size() - 1; i >= 0; --i) {
            for (int j = grid[0].size() - 1; j >= 0; --j) {
                if (grid[i][j] != 'W') {
                    if (i + 1 < grid.size()) {
                        down[i][j] = down[i + 1][j];
                    }
                    if (j + 1 < grid[0].size()) {
                        right[i][j] = right[i][j + 1];
                    }
                    if (grid[i][j] == 'E') {
                        ++down[i][j];
                        ++right[i][j];
                    }
                }
            }
        }

        int left = 0;
        vector<int> up(grid[0].size());
        for (int i = 0; i < grid.size(); ++i) {
            left = 0;
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == 'W') {
                    up[j] = 0;
                    left = 0;
                } else if (grid[i][j] == 'E') {
                    ++up[j];
                    ++left;
                } else {
                    result = max(result, left + up[j] + right[i][j] + down[i][j]);
                }
            }
        }

        return result;
    }


