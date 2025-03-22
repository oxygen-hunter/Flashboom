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


    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
        // 1. max(|arr1[i]-arr1[j]| + |arr2[i]-arr2[j]| + |i-j| for i > j)
        //    = max(|arr1[i]-arr1[j]| + |arr2[i]-arr2[j]| + |i-j| for j > i)
        // 2. for i > j:
        //        (|arr1[i]-arr1[j]| + |arr2[i]-arr2[j]| + |i-j|)
        //        >= c1*(arr1[i]-arr1[j]) + c2*(arr2[i]-arr2[j]) + i-j for c1 in (1, -1), c2 in (1, -1)
        //        = (c1*arr1[i]+c2*arr2[i]+i) - (c1*arr1[j]+c2*arr2[j]+j) for c1 in (1, -1), c2 in (1, -1)
        // 1 + 2 => max(|arr1[i]-arr1[j]| + |arr2[i]-arr2[j]| + |i-j| for i != j)
        //          = max((c1*arr1[i]+c2*arr2[i]+i) - (c1*arr1[j]+c2*arr2[j]+j)
        //                for c1 in (1, -1), c2 in (1, -1) for i > j)
        int result = 0;
        for (const auto& c1 : {1, -1}) {
            for (const auto& c2 : {1, -1}) {
                int min_prev = c1 * arr1[0] + c2 * arr2[0] + 0;
                for (int i = 1; i < arr1.size(); ++i) {
                    const auto& curr = c1 * arr1[i] + c2 * arr2[i] + i;
                    result = max(result, curr - min_prev);
                    min_prev = min(min_prev, curr);
                }
            }
        }
        return result;
    }


