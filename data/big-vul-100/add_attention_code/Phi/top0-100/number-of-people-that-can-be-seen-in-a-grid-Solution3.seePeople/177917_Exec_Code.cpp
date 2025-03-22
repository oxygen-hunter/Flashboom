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

    vector<vector<int>> seePeople(vector<vector<int>>& heights) {
        vector<vector<int>> result(size(heights), vector<int>(size(heights[0])));
        const auto& count = [](const auto& height, int i, vector<int> *stk, const auto& increase) {
            while (!empty(*stk) && height(stk->back()) < height(i)) {
                increase(stk->back()); stk->pop_back();
            }
            if (!empty(*stk)) {
                increase(stk->back());
            }
            if (!empty(*stk) && height(stk->back()) == height(i)) {
                stk->pop_back();
            }
            stk->emplace_back(i);
        };

        for (int i = 0; i < size(heights); ++i) {
            const auto& height = [&](int x) {
                return heights[i][x];
            };
            const auto& increase = [&](int x) {
                ++result[i][x];
            };
            vector<int> stk;
            for (int j = 0; j < size(heights[0]); ++j) {
                count(height, j, &stk, increase);
            }
        }
        for (int j = 0; j < size(heights[0]); ++j) {
            const auto& height = [&](int x) {
                return heights[x][j];
            };
            const auto& increase = [&](int x) {
                ++result[x][j];
            };
            vector<int> stk;
            for (int i = 0; i < size(heights); ++i) {
                count(height, i, &stk, increase);
            }
        }
        return result;
    }

