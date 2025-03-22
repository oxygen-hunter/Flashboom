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


    int maxStarSum(vector<int>& vals, vector<vector<int>>& edges, int k) {
        vector<vector<int>> adj(size(vals));
        for (const auto& e : edges) {
            if (vals[e[1]] > 0) {
                adj[e[0]].emplace_back(e[1]);
            }
            if (vals[e[0]] > 0) {
                adj[e[1]].emplace_back(e[0]);
            }
        }
        int result = numeric_limits<int>::min();
        for (int u = 0; u < size(vals); ++u) {
            if (1 <= k && k <= size(adj[u])) {
                nth_element(begin(adj[u]), begin(adj[u]) + k - 1, end(adj[u]),
                            [&](const auto& a, const auto& b) {
                                return vals[a] > vals[b];
                            });
            }
            result = max(result, vals[u] + accumulate(cbegin(adj[u]), cbegin(adj[u]) + min(k, static_cast<int>(size(adj[u]))), 0,
                                                      [&](const auto& total, const auto& x) {
                                                          return total + vals[x];
                                                      }));
        }
        return result;
    }


