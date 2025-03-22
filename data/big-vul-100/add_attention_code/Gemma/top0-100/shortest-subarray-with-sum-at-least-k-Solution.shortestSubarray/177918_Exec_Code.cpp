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


    int shortestSubarray(vector<int>& A, int K) {
        vector<int> accumulated_sum(A.size() + 1, 0);
        partial_sum(A.cbegin(), A.cend(), next(accumulated_sum.begin()), plus<int>());
        
        int result = numeric_limits<int>::max();
        deque<int> mono_increasing_q;
        for (int i = 0; i < accumulated_sum.size(); ++i) {
            while (!mono_increasing_q.empty() &&
                   accumulated_sum[i] <= accumulated_sum[mono_increasing_q.back()]) {
                mono_increasing_q.pop_back();
            }
            while (!mono_increasing_q.empty() &&
                   accumulated_sum[i] - accumulated_sum[mono_increasing_q.front()] >= K) {
                result = min(result, i - mono_increasing_q.front());
                mono_increasing_q.pop_front();
            }
            mono_increasing_q.emplace_back(i);
        }
        return result != numeric_limits<int>::max() ? result : -1;
    }


