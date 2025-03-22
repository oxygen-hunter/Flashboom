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


    bool find(const string& word, TrieNode *curr, int i, bool mistakeAllowed) {
        if (i == word.length()) {
            return curr->isString && !mistakeAllowed; 
        }

        if (!curr->leaves.count(word[i])) {
            return mistakeAllowed ?
                       any_of(curr->leaves.begin(), curr->leaves.end(),
                              [&](const pair<char, TrieNode *>& kvp) { 
                                  return find(word, kvp.second, i + 1, false);
                               }) :
                       false;
        }
                    
        if (mistakeAllowed) {
            return find(word, curr->leaves[word[i]], i + 1, true) ||
                   any_of(curr->leaves.begin(), curr->leaves.end(),
                          [&](const pair<char, TrieNode *>& kvp) { 
                              return kvp.first != word[i] && find(word, kvp.second, i + 1, false);
                          });
        }
        return find(word, curr->leaves[word[i]], i + 1, false);
    }


