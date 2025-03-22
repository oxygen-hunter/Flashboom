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

    int minimumSeconds(vector<vector<string>>& land) {
        static const vector<pair<int, int>> DIRECTIONS {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        vector<vector<int>> lookup1(size(land), vector<int>(size(land[0]), -1));
        vector<vector<int>> lookup2(size(land), vector<int>(size(land[0]), -1));
        vector<pair<int, int>> q1;
        vector<pair<int, int>> q2;
        for (int i = 0; i < size(land); ++i) {
            for (int j = 0; j < size(land[0]); ++j) {
                if (land[i][j] == "*") {
                    q1.emplace_back(i, j);
                    lookup2[i][j] = 0;
                } else if (land[i][j] == "S") {
                    q2.emplace_back(i, j);
                    lookup2[i][j] = 0;
                }
            }
        }
        while (!empty(q1) || !empty(q2)) {
            vector<pair<int, int>> new_q1;
            vector<pair<int, int>> new_q2;
            for (const auto& [i, j] : q1) {
                for (const auto& [di, dj] : DIRECTIONS) {
                    const int ni = i + di, nj = j + dj;
                    if (!(0 <= ni && ni < size(land) && 0 <= nj && nj < size(land[0]) && land[ni][nj] != "X" && land[ni][nj] != "D" && lookup1[ni][nj] == -1)) {
                        continue;
                    }
                    lookup1[ni][nj] = 0;
                    new_q1.emplace_back(ni, nj);
                }
            }
            for (const auto& [i, j] : q2) {
                if (land[i][j] == "D") {
                    return lookup2[i][j];
                }
                for (const auto& [di, dj] : DIRECTIONS) {
                    const int ni = i + di, nj = j + dj;
                    if (!(0 <= ni && ni < size(land) && 0 <= nj && nj < size(land[0]) && land[ni][nj] != "X" && lookup2[ni][nj] == -1 && lookup1[ni][nj] == -1)) {
                        continue;
                    }
                    lookup2[ni][nj] = lookup2[i][j] + 1;
                    new_q2.emplace_back(ni, nj);
                }
            }
            q1 = move(new_q1);
            q2 = move(new_q2);
        }
        return -1;
    }

