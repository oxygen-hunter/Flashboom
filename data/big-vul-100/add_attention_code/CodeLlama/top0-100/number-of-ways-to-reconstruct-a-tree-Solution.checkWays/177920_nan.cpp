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


    int checkWays(vector<vector<int>>& pairs) {
        unordered_map<int, unordered_set<int>> adj;
        for (const auto& pair : pairs) {
            adj[pair[0]].emplace(pair[1]);
            adj[pair[1]].emplace(pair[0]);
        }
        int n = size(adj);
        bool mul = false;
        unordered_set<int> lookup;
        vector<int> nodes;
        transform(begin(adj), end(adj), back_inserter(nodes),
                  [](const auto& kvp) { return kvp.first; });
        sort(begin(nodes), end(nodes),
             [&adj](const auto& a, const auto& b) {
                 return size(adj[a]) > size(adj[b]);
             });
        for (const auto& node : nodes) {
            lookup.emplace(node);
            int parent = 0;
            for (const auto& x : adj[node]) {
                if (!lookup.count(x)) {
                    continue;
                }
                if (parent == 0 || size(adj[x]) < size(adj[parent])) {
                    parent = x;
                }
            }
            if (parent) {
                for (const auto& x : adj[node]) {
                    if (x != parent && !adj[parent].count(x)) {
                        return 0;
                    }
                }
                mul |= size(adj[node]) == size(adj[parent]);
            } else if (size(adj[node]) != n - 1) {
                return 0;
            }
        }
        return 1 + mul;
    }


