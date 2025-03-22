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
	    chend = ch + (rlen + 1);
 	    length = *ch;
 	    for (i = 0; i < rep.nExtensions; i++) {
 		if (ch + length < chend) {
 		    list[i] = ch+1;  /* skip over length */
 		    ch += length + 1; /* find next length ... */
		    if (ch <= chend) {
			length = *ch;
			*ch = '\0'; /* and replace with null-termination */
			count++;
		    } else {
			list[i] = NULL;
		    }
 		} else
 		    list[i] = NULL;
 	    }
		    }
		} else

    long long maximumScore(vector<vector<int>>& grid) {
        vector<int64_t> prefix(size(grid)+ 1);
        for (int i = 0; i < size(grid); ++i) {
            prefix[i + 1] = prefix[i] + grid[i][0];
        }
        // dp[0][i]: the maximum score from 0 to the current column, and the current column has i black cells, without scoring the white cells of the current column
        // dp[1][i]: the maximum score from 0 to the current column, and the current column has i black cells, with scoring the white cells of the current column
        vector<vector<int64_t>> dp(2, vector<int64_t>(size(grid) + 1));
        for (int j = 1; j < size(grid[0]); ++j) {
            vector<int64_t> new_prefix(size(grid)+ 1);
            for (int i = 0; i < size(grid); ++i) {
                new_prefix[i + 1] = new_prefix[i] + grid[i][j];
            }
            vector<vector<int64_t>> new_dp(2, vector<int64_t>(size(grid) + 1));
            for (int i = 0; i <= size(grid); ++i) {
                for (int k = 0; k <= size(grid); ++k) {
                    new_dp[0][i] = max(new_dp[0][i], max(prefix[i] - prefix[k], static_cast<int64_t>(0)) + dp[0][k]);
                    new_dp[1][i] = max(new_dp[1][i], dp[1][k] + max(new_prefix[k] - new_prefix[i], static_cast<int64_t>(0)));
                }
                new_dp[0][i] = max(new_dp[0][i], ranges::max(dp[1]));
                new_dp[1][i] = max(new_dp[1][i], new_dp[0][i]);
            }
            dp = move(new_dp);
            prefix = move(new_prefix);
        }
        return ranges::max(dp[1]);
    }

