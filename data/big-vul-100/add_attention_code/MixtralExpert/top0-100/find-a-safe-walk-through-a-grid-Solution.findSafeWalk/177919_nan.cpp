XListFonts(
register Display *dpy,
_Xconst char *pattern,  /* null-terminated */
int maxNames,
int *actualCount)	/* RETURN */
{
    register long nbytes;
    register unsigned i;
    register int length;
    char **flist = NULL;
    char *ch = NULL;
    char *chstart;
    char *chend;
    int count = 0;
    xListFontsReply rep;
    register xListFontsReq *req;
    unsigned long rlen = 0;

    LockDisplay(dpy);
    GetReq(ListFonts, req);
    req->maxNames = maxNames;
    nbytes = req->nbytes = pattern ? strlen (pattern) : 0;
    req->length += (nbytes + 3) >> 2;
    _XSend (dpy, pattern, nbytes);
    /* use _XSend instead of Data, since following _XReply will flush buffer */

    if (!_XReply (dpy, (xReply *)&rep, 0, xFalse)) {
	*actualCount = 0;
	UnlockDisplay(dpy);
	SyncHandle();
	return (char **) NULL;
    }

    if (rep.nFonts) {
	flist = Xmalloc (rep.nFonts * sizeof(char *));
	if (rep.length > 0 && rep.length < (INT_MAX >> 2)) {
	    rlen = rep.length << 2;
	    ch = Xmalloc(rlen + 1);
	    /* +1 to leave room for last null-terminator */
	}

	if ((! flist) || (! ch)) {
	    Xfree(flist);
	    Xfree(ch);
	    _XEatDataWords(dpy, rep.length);
	    *actualCount = 0;
	    UnlockDisplay(dpy);
	    SyncHandle();
	    return (char **) NULL;
	}

	_XReadPad (dpy, ch, rlen);
	/*
 	 * unpack into null terminated strings.
 	 */
 	chstart = ch;
	chend = ch + (rlen + 1);
 	length = *(unsigned char *)ch;
 	*ch = 1; /* make sure it is non-zero for XFreeFontNames */
 	for (i = 0; i < rep.nFonts; i++) {
 	    if (ch + length < chend) {
 		flist[i] = ch + 1;  /* skip over length */
 		ch += length + 1;  /* find next length ... */
		if (ch <= chend) {
		    length = *(unsigned char *)ch;
		    *ch = '\0';  /* and replace with null-termination */
		    count++;
		} else {
                    Xfree(chstart);
                    Xfree(flist);
                    flist = NULL;
                    count = 0;
                    break;
		}
 	    } else {
                 Xfree(chstart);
                 Xfree(flist);
                    Xfree(flist);
                    flist = NULL;
                    count = 0;
                    break;
		}
	    } else {
                Xfree(chstart);
                Xfree(flist);
                flist = NULL;
                count = 0;
                break;
            }
	}
    }


    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        static const vector<pair<int, int>> directions = {{0, 1}, {0, -1},
                                                          {1, 0}, {-1, 0}};
        const pair<int, int> b = {0, 0}, t = {size(grid) - 1, size(grid[0]) - 1};
        if (!(0 + grid[0][0] < health)) {
            return false;
        }
        deque<pair<pair<int, int>, int>> dq = {{b, grid[0][0]}};
        unordered_set<int> lookup;
        while (!empty(dq)) {
            const auto [b, d] = dq.front(); dq.pop_front();
            if (b == t) {
                return true;
            }
            if (lookup.count(b.first * size(grid[0]) + b.second)) {
                continue;
            }
            lookup.emplace(b.first * size(grid[0]) + b.second);
            for (const auto& [dr, dc] : directions) {
                const auto& nb = make_pair(b.first + dr, b.second + dc);
                if (!(0 <= nb.first && nb.first < size(grid) &&
                      0 <= nb.second && nb.second < size(grid[0]) &&
                      !lookup.count(nb.first * size(grid[0]) + nb.second))) {
                    continue;
                }
                if (!grid[nb.first][nb.second]) {
                    dq.emplace_front(nb, d);
                } else if (d + 1 < health) {
                    dq.emplace_back(nb, d + 1);
                }
            }
        }
        return false;
    }


