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


    vector<vector<int>> findRLEArray(vector<vector<int>>& encoded1, vector<vector<int>>& encoded2) {
        vector<vector<int>> result;
        for (int i = 0, j = 0, remain1 = 0, remain2 = 0;
             (remain1 || i < size(encoded1)) && (remain2 || j < size(encoded2));) {
            if (!remain1) {
                remain1 = encoded1[i++][1];
            }
            if (!remain2) {
                remain2 = encoded2[j++][1];
            }
            int cnt = min(remain1, remain2);
            remain1 -= cnt;
            remain2 -= cnt;
            if (!empty(result) && result.back()[0] == encoded1[i - 1][0] * encoded2[j - 1][0]) {
                result.back()[1] += cnt;
            } else {
                result.push_back({encoded1[i - 1][0] * encoded2[j - 1][0], cnt});
            }
        }
        return result;
    }


