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


    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        if (n == 1) {
            return {0};
        }

        unordered_map<int, unordered_set<int>> neighbors;
        for (const auto& e : edges) {
            int u, v;
            tie(u, v) = e;
            neighbors[u].emplace(v);
            neighbors[v].emplace(u);
        }

        vector<int> pre_level, cur_level;
        unordered_set<int> unvisited;
        for (int i = 0; i < n; ++i) {
            if (neighbors[i].size() == 1) {  // A leaf.
                pre_level.emplace_back(i);
            }
            unvisited.emplace(i);
        }

        // A graph can have 2 MHTs at most.
        // BFS from the leaves until the number 
        // of the unvisited nodes is less than 3.
        while (unvisited.size() > 2) {
            cur_level.clear();
            for (const auto& u : pre_level) {
                unvisited.erase(u);
                for (const auto& v : neighbors[u]) {
                    if (unvisited.count(v)) { 
                        neighbors[v].erase(u);
                        if (neighbors[v].size() == 1) {
                            cur_level.emplace_back(v);
                        }
                    }
                }
            }
            swap(pre_level, cur_level);
        }

        vector<int> res(unvisited.begin(), unvisited.end());
        return res;
    }


