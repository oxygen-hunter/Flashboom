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

    int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
        static const int INF = numeric_limits<int>::max();

        const auto& bit_length = [](int x) {
            return (x ? std::__lg(x) : -1) + 1;
        };

        const int FULL_MASK = (1 << bit_length(ranges::max(nums))) - 1;
        vector<vector<unordered_map<int, int>>> lookup(size(nums), vector<unordered_map<int, int>>(size(andValues)));
        const function<int (int, int, int)> memoization = [&](int i, int j, int mask) {
            if (i == size(nums) && j == size(andValues)) {
                return 0;
            }
            if (i == size(nums) || j == size(andValues) || mask < andValues[j]) {
                return INF;
            }
            if (!lookup[i][j].count(mask)) {
                int curr = memoization(i + 1, j, mask & nums[i]);
                if ((mask & nums[i]) == andValues[j]) {
                    const int total = memoization(i + 1, j + 1, FULL_MASK);
                    if (total != INF) {
                        curr = min(curr, nums[i] + total);
                    }
                }
                lookup[i][j][mask] = curr;
            }
            return lookup[i][j][mask];
        };

        const int result = memoization(0, 0, FULL_MASK);
        return result != INF ? result : -1;
    }

