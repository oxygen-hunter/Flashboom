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

    long long maxBalancedSubsequenceSum(vector<int>& nums) {
        static const auto NEG_INF = numeric_limits<int64_t>::min();

        unordered_set<int> vals_set;
        for (int i = 0; i < size(nums); ++i) {
            vals_set.emplace(nums[i] - i);
        }
        vector<int> sorted_vals(cbegin(vals_set), cend(vals_set));
        sort(begin(sorted_vals), end(sorted_vals));
        unordered_map<int, int> val_to_idx;
        for (int i = 0; i < size(sorted_vals); ++i) {
            val_to_idx[sorted_vals[i]] = i;
        }
        SegmentTree<int64_t> st(size(val_to_idx));
        for (int i = 0; i < size(nums); ++i) {
            const auto val = max(st.query(0, val_to_idx[nums[i] - i]), static_cast<int64_t>(0)) + nums[i];
            st.update(val_to_idx[nums[i] - i], val);
        }
        return st.query(0, size(val_to_idx) - 1);
    }

