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

    vector<int> numberOfAlternatingGroups(vector<int>& colors, vector<vector<int>>& queries) {
        const int n = size(colors);
        set<int> bst;
        BIT bit1(n + 1), bit2(n + 1);
        const auto& update = [&](int i, int d) {
            if (d == +1) {
                bst.emplace(i);
                if (size(bst) == 1) {
                    bit1.add(n, +1);
                    bit2.add(n, +n);
                }
            }
            auto curr = bst.find(i);
            auto prv = prev(curr != begin(bst) ? curr : end(bst));
            auto nxt = next(curr);
            if (nxt == end(bst)) {
                nxt = begin(bst);
            }
            if (size(bst) != 1) {
                int l = ((*nxt) - (*prv) + (n - 1)) % n + 1;
                bit1.add(l, d * -1);
                bit2.add(l, d * -l);
                l = ((*curr) - (*prv) + n) % n;
                bit1.add(l, d * +1);
                bit2.add(l, d * +l);
                l = ((*nxt) - (*curr) + n) % n;
                bit1.add(l, d * +1);
                bit2.add(l, d * +l);
            }
            if (d == -1) {
                if (size(bst) == 1) {
                    bit1.add(n, -1);
                    bit2.add(n, -n);
                }
                bst.erase(curr);
            }
        };

        vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (colors[i] == colors[(i + 1) % n]) {
                update(i, +1);
            }
        }
        for (const auto &q : queries) {
            if (q[0] == 1) {
                const int l = q[1];
                result.emplace_back(!empty(bst) ? (bit2.query(n) - bit2.query(l - 1)) - 
                                                  (l - 1) * (bit1.query(n) - bit1.query(l - 1)) : n);
                continue;
            }
            const int i = q[1];
            if (colors[i] == q[2]) {
                continue;
            }
            colors[i] = q[2];
            update((i - 1 + n) % n, colors[i] == colors[(i - 1 + n) % n] ? +1 : -1);
            update(i, colors[i] == colors[(i + 1) % n] ? +1 : -1);
        }
        return result;
    }

