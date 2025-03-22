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

    int maxSumMinProduct(vector<int>& nums) {
        static const int MOD = 1e9 + 7;

        vector<int64_t> prefix(nums.size() + 1);
        for (int i = 0; i < size(nums); ++i) {
           prefix[i + 1] = prefix[i] + nums[i];
        }
        vector<int> stk = {-1};
        int64_t result = 0;
        for (int i = 0; i <= size(nums); ++i) {
            while (stk.back() != -1 && (i == size(nums) || nums[stk.back()] >= nums[i])) {
                int j = stk.back();
                stk.pop_back();
                result = max(result, nums[j] * (prefix[(i - 1) + 1] - prefix[stk.back() + 1]));
            }
            stk.emplace_back(i);
        }
        return result % MOD;
    }

