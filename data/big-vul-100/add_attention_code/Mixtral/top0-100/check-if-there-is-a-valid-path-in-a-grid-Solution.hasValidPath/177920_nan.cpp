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
	    chend = ch + (nbytes + 1);
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

