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


    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
        vector<vector<unordered_set<int>>> neighbors(n, vector<unordered_set<int>>(2));
        for (const auto& edge : red_edges) {
            neighbors[edge[0]][0].emplace(edge[1]);
        }
        for (const auto& edge : blue_edges) {
            neighbors[edge[0]][1].emplace(edge[1]);
        }
        const auto& INF = max(2 * n - 3, 0) + 1;
        vector<vector<int>> dist(n, vector<int>(2, INF));
        dist[0] = {0, 0};
        queue<pair<int, int>> q({{0, 0}, {0, 1}});
        while (!q.empty()) {
            int i, c;
            tie(i, c) = q.front(); q.pop();
            for (const auto& j : neighbors[i][c]) {
                if (dist[j][c] != INF) {
                    continue;
                }
                dist[j][c] = dist[i][1 ^ c] + 1;
                q.emplace(j, 1 ^ c);
            }
        }
        vector<int> result;
        for (const auto& d : dist) {
            const auto& x = *min_element(d.cbegin(), d.cend());
            result.emplace_back((x != INF) ? x : -1);
        }
        return result;
    }


