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


    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        vector<function<bool (int, int)>> checks = {
            [&mat, &target](int i, int j) { return mat[i][j] == target[i][j]; },
            [&mat, &target](int i, int j) { return mat[i][j] == target[j][size(mat) - 1 - i]; },
            [&mat, &target](int i, int j) { return mat[i][j] == target[size(mat) - 1 - i][size(mat[0]) - 1 - j]; },
            [&mat, &target](int i, int j) { return mat[i][j] == target[size(mat[0]) - 1 - j][i]; },
        };
        const auto& traverse = [&mat, &target](const auto& check) {
            for (int i = 0; i < size(mat); ++i) {
                for (int j = 0; j < size(mat[0]); ++j) {
                    if (!check(i, j)) {
                        return false;
                    }
                }
            }
            return true;
        };
        for (const auto& check : checks) {
            if (traverse(check)) {
                return true;
            }
        }
        return false;
    }


