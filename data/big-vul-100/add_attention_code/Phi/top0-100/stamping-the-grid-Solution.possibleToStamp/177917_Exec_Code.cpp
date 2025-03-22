char **XGetFontPath(
    register Display *dpy,
    int *npaths)	/* RETURN */
{
	xGetFontPathReply rep;
	unsigned long nbytes = 0;
	char **flist = NULL;
	char *ch = NULL;
	char *chend;
	int count = 0;
	register unsigned i;
	register int length;
	_X_UNUSED register xReq *req;

	LockDisplay(dpy);
	GetEmptyReq (GetFontPath, req);
	(void) _XReply (dpy, (xReply *) &rep, 0, xFalse);

	if (rep.nPaths) {
	    flist = Xmalloc(rep.nPaths * sizeof (char *));
	    if (rep.length < (INT_MAX >> 2)) {
		nbytes = (unsigned long) rep.length << 2;
		ch = Xmalloc (nbytes + 1);
                /* +1 to leave room for last null-terminator */
	    }

	    if ((! flist) || (! ch)) {
		Xfree(flist);
		Xfree(ch);
		_XEatDataWords(dpy, rep.length);
		UnlockDisplay(dpy);
		SyncHandle();
		return (char **) NULL;
	    }

	    _XReadPad (dpy, ch, nbytes);
	    /*
 	     * unpack into null terminated strings.
 	     */
 	    chend = ch + nbytes;
	    length = *ch;
 	    for (i = 0; i < rep.nPaths; i++) {
 		if (ch + length < chend) {
 		    flist[i] = ch+1;  /* skip over length */
 		    ch += length + 1; /* find next length ... */
		    length = *ch;
 		    *ch = '\0'; /* and replace with null-termination */
 		    count++;
 		} else
		    flist[i] = NULL;
	    }
	}
	*npaths = count;
	UnlockDisplay(dpy);
	SyncHandle();
	return (flist);
}

    bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) {
        vector<vector<int>> prefix(size(grid) + 1, vector<int>(size(grid[0]) + 1));
        vector<vector<int>> fit(size(grid), vector<int>(size(grid[0])));
        for (int i = 0; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]); ++j) {
                prefix[i + 1][j + 1] = prefix[i + 1][j] + prefix[i][j + 1] - prefix[i][j] + (1 ^ grid[i][j]);
                if (i + 1 >= stampHeight && j + 1 >= stampWidth) {
                    const int x = i + 1 - stampHeight, y = j + 1 - stampWidth;
                    fit[i][j] = static_cast<int>(prefix[i + 1][j + 1] - prefix[x][j + 1] - prefix[i + 1][y] + prefix[x][y] == stampWidth * stampHeight);
                }
            }
        }
        vector<vector<int>> prefix2(size(grid) + 1, vector<int>(size(grid[0]) + 1));
        for (int i = 0; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]); ++j) {
                prefix2[i + 1][j + 1] = prefix2[i + 1][j] + prefix2[i][j + 1] - prefix2[i][j] + fit[i][j];
            }
        }
        for (int i = 0; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]); ++j) {
                const int x = min(i + stampHeight, static_cast<int>(size(grid))), y = min(j + stampWidth, static_cast<int>(size(grid[0])));
                if (!grid[i][j] && !(prefix2[x][y] - prefix2[i][y] - prefix2[x][j] + prefix2[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }

