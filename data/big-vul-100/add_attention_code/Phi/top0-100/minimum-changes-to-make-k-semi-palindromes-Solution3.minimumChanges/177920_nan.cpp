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

    int minimumChanges(string s, int k) {
        vector<vector<int>> divisors(size(s) + 1);
        for (int i = 1; i < size(divisors); ++i) {  // Time: O(nlogn), Space: O(nlogn)
            for (int j = i + i; j < size(divisors); j += i) {
                divisors[j].emplace_back(i);
            }
        }

        const auto& dist = [&](int left, int right, int d) {
            int result = 0;
            for (int i = 0; i < (right - left + 1) / 2; ++i) {
                if (s[left + i] != s[right - ((i / d + 1) * d - 1) + (i % d)]) {
                    ++result;
                }
            }
            return result;
        };

        const auto& min_dist = [&](int left, int right) {  // Time: O(nlogn)
            int result = size(s);
            for (const auto& d : divisors[right - left + 1]) {
                result = min(result, dist(left, right, d));
            }
            return result;
        };
            
        vector<vector<int>> dp(size(s) + 1, vector<int>(k + 1, size(s)));
        dp[0][0] = 0;
        for (int i = 0; i < size(s); ++i) {  // Time: O(n^2 * nlogn + n^2 * k), Space: O(n * k)
            for (int j = 0; j < i; ++j) {
                const int c = min_dist(j, i);
                for (int l = 0; l < k; ++l) {
                    dp[i + 1][l + 1] = min(dp[i + 1][l + 1], dp[j][l] + c);
                }
            }
        }
        return dp[size(s)][k];
    }

