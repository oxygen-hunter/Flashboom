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


    bool hasValidPath(vector<vector<int>>& grid) {
        static const pair<int, int> E = {0,  1}, S = {1,  0},
                                    W = {0, -1}, N = {-1, 0};
        static const vector<vector<pair<int, int>>> directions = {
            {W, E}, {N, S},
            {W, S}, {S, E},
            {W, N}, {N, E}
        };

        for (auto [r, c] : directions.at(grid[0][0] - 1)) {
            if (!(0 <= r && r < grid.size() &&
                  0 <= c && c < grid[0].size())) {
                continue;
            }
            int pr = 0, pc = 0;
            while (r != grid.size() - 1 || c != grid[0].size() - 1) {
                bool is_found = false;
                for (const auto& [dx, dy] : directions.at(grid[r][c] - 1)) {
                    const auto& [nr, nc] = pair(r + dx, c + dy);
                    if ((nr == pr && nc == pc) ||
                        !(0 <= nr && nr < grid.size() &&
                          0 <= nc && nc < grid[0].size())) {
                        continue;
                    }
                    const auto& dirs = directions.at(grid[nr][nc] - 1);
                    if (find(cbegin(dirs), cend(dirs), pair(-dx, -dy)) == cend(dirs)) {
                        continue;
                    }
                    tie(pr, pc, r, c) = tuple(r, c, nr, nc);
                    is_found = true;
                    break;
                }
                if (!is_found) {
                    return false;
                }
            }
            return true;
        }
        return grid.size() == 1 && grid[0].size() == 1;
    }


