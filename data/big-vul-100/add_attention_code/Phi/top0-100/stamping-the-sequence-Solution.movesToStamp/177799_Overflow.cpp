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

    vector<int> movesToStamp(string stamp, string target) {
        const int M = stamp.size(), N = target.size();
        
        queue<int> q;
        vector<bool> lookup(N);
        vector<int> result;
        vector<pair<unordered_set<int>, unordered_set<int>>> A;
        for (int i = 0; i < N - M + 1; ++i) {
            unordered_set<int> made, todo;
            for (int j = 0; j < M; ++j) {
                if (stamp[j] == target[i + j]) {
                    made.emplace(i + j);
                } else {
                    todo.emplace(i + j);
                }
            }
            A.emplace_back(made, todo);
            if (!todo.empty()) {
                continue;
            }
            result.emplace_back(i);
            for (const auto& m : made) {
                if (lookup[m]) {
                    continue;
                }
                q.emplace(m);
                lookup[m] = true;
            }
        }
        
        while (!q.empty()) {
            auto i = q.front(); q.pop();
            for (int j = max(0, i - M + 1); j < min(N - M, i) + 1; ++j) {
                unordered_set<int>& made = A[j].first;
                unordered_set<int>& todo = A[j].second;
                if (!todo.count(i)) {
                    continue;
                }
                todo.erase(i);
                if (!todo.empty()) {
                    continue;
                }
                result.emplace_back(j);
                for (const auto& m : made) {
                    if (lookup[m]) {
                        continue;
                    }
                    q.emplace(m);
                    lookup[m] = true;
                }
            }
        }
        if (std::all_of(lookup.cbegin(), lookup.cend(), [](bool i){ return i; })) {
            reverse(result.begin(), result.end());
            return result;
        }
        return {};
    }

