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

    int minimumLines(vector<vector<int>>& points) {
        auto ceil_divide = [](int a, int b) {
            return (a + b - 1) / b;
        };
        unordered_map<tuple<int, int, int>, unordered_set<pair<int, int>, PairHash<int>>, TupleHash<int, int, int>> lookup;
        for (int i = 0; i < size(points); ++i) {
            const int x1 = points[i][0], y1 = points[i][1];
            for (int j = i + 1; j < size(points); ++j) {
                const int x2 = points[j][0], y2 = points[j][1];
                // (x-x1)/(x2-x1) = (y-y1)/(y2-y1)
                // => (y2-y1)x - (x2-x1)y = x1(y2-y1) - y1(x2-x1)
                int a = y2 - y1;
                int b = -(x2 - x1);
                int c = x1 * (y2 - y1) - y1 * (x2 - x1);
                const int g = gcd(gcd(a, b), c);
                a /= g, b /= g, c /= g;
                lookup[{a, b, c}].emplace(x1, y1);
                lookup[{a, b, c}].emplace(x2, y2);
            }
        }
        vector<tuple<int, int, int>> lines;
        for (const auto& [l, p] : lookup) {
            if (size(p) > 2) {  // filter to improve complexity
                lines.emplace_back(l);
            }
        }
        assert(size(lines) <= size(points) / 2);  // 1 extra colinear point per 2 points
        int result = numeric_limits<int>::max();
        const int mask_upper_bound = 1 << size(lines);
        for (int mask = 0; mask < mask_upper_bound; ++mask) {
            unordered_set<pair<int, int>, PairHash<int>> covered;
            for (int i = 0, bit = 1; bit <= mask; bit <<= 1, ++i) {
                if (mask & bit) {
                    for (const auto& x : lookup[lines[i]]) {
                        covered.emplace(x);
                    }
                }
            }
            result = min(result, __builtin_popcount(mask) + ceil_divide(size(points) - size(covered), 2));
        }
        return result;
    }

