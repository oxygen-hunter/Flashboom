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


    vector<int> timeTaken(vector<int>& arrival, vector<int>& state) {
        enum {UNKNOWN = -1, ENTERING, EXITING};
        vector<int> result(size(arrival));
        int curr = numeric_limits<int>::min(), direction = UNKNOWN;
        vector<queue<int>> q(2);
        const auto& go_until = [&](int t) {
            while (curr <= t && any_of(cbegin(q), cend(q), [](const auto& x) { return !empty(x); })) {
                if (empty(q[direction])) {
                    direction ^= 1;
                }
                result[q[direction].front()] = curr++;
                q[direction].pop();
            }
        };

        for (int i = 0; i < size(arrival); ++i) {
            go_until(arrival[i] - 1);
            q[state[i]].emplace(i);
            if (!(arrival[i] <= curr)) {
                curr = arrival[i], direction = EXITING;
            }
        }
        go_until(numeric_limits<int>::max());
        return result;
    }


