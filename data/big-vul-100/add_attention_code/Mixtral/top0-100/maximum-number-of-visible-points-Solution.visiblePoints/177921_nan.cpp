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

    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        static const double PI = atan2(0, -1);

        vector<double> arr;
        int extra = 0;
        for (const auto& p : points) {
            if (p == location) {
                ++extra;
                continue;
            }
            arr.emplace_back(atan2(p[1] - location[1], p[0] - location[0]));
        }
        sort(begin(arr), end(arr));
        const int n = size(arr);
        for (int i = 0; i < n; ++i) {  // make it circular
            arr.emplace_back(arr[i] + 2.0 * PI);
        }
        const double d = 2.0 * PI * (angle / 360.0);
        int result = 0;
        for (int left = 0, right = 0; right < size(arr); ++right) {
            while (arr[right] - arr[left] > d) {
                ++left;
            }
            result = max(result, right - left + 1);
        }
        return result + extra;
    }

