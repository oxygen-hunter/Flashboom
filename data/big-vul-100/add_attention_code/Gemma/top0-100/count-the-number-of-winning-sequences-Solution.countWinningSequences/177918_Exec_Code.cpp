char **XListExtensions(
    register Display *dpy,
    int *nextensions)	/* RETURN */
{
	xListExtensionsReply rep;
	char **list = NULL;
	char *ch = NULL;
	char *chend;
	int count = 0;
	register unsigned i;
	register int length;
	_X_UNUSED register xReq *req;
	unsigned long rlen = 0;

	LockDisplay(dpy);
	GetEmptyReq (ListExtensions, req);

	if (! _XReply (dpy, (xReply *) &rep, 0, xFalse)) {
	    UnlockDisplay(dpy);
	    SyncHandle();
	    return (char **) NULL;
	}

	if (rep.nExtensions) {
	    list = Xmalloc (rep.nExtensions * sizeof (char *));
	    if (rep.length > 0 && rep.length < (INT_MAX >> 2)) {
		rlen = rep.length << 2;
		ch = Xmalloc (rlen + 1);
                /* +1 to leave room for last null-terminator */
	    }

	    if ((!list) || (!ch)) {
		Xfree(list);
		Xfree(ch);
		_XEatDataWords(dpy, rep.length);
		UnlockDisplay(dpy);
		SyncHandle();
		return (char **) NULL;
	    }

	    _XReadPad (dpy, ch, rlen);
	    /*
 	     * unpack into null terminated strings.
 	     */
 	    chend = ch + rlen;
	    length = *ch;
 	    for (i = 0; i < rep.nExtensions; i++) {
 		if (ch + length < chend) {
 		    list[i] = ch+1;  /* skip over length */
 		    ch += length + 1; /* find next length ... */
		    length = *ch;
 		    *ch = '\0'; /* and replace with null-termination */
 		    count++;
 		} else
		    list[i] = NULL;
	    }
	}

	*nextensions = count;
	UnlockDisplay(dpy);
	SyncHandle();
	return (list);
}


    int countWinningSequences(string s) {
        static const int MOD = 1e9 + 7;
        static const unordered_map<char, int> lookup = {{'F', 0}, {'W', 1}, {'E', 2}};

        vector<unordered_map<int, int>> dp(3);
        for (int i = 0; i < size(s); ++i) {
            vector<unordered_map<int, int>> new_dp(3);
            const auto x = lookup.at(s[i]);
            for (int j = 0; j < 3; ++j) {
                const int diff = ((j - x + 1) % 3 + 3) % 3 - 1;
                if (i == 0) {
                    new_dp[j][diff] = 1;
                    continue;
                }
                for (int k = 0; k < 3; ++k) {
                    if (k == j) {
                        continue;
                    }
                    for (const auto& [v, c] : dp[k]) {
                        new_dp[j][v + diff] = (new_dp[j][v + diff] + c) % MOD;
                    }
                }
            }
            dp = move(new_dp);
        }
        int result = 0;
        for (int j = 0; j < 3; ++j) {
            for (const auto& [v, c] : dp[j]) {
                if (v >= 1) {
                    result = (result + c) % MOD;
                }
            }
        }
        return result;
    }


