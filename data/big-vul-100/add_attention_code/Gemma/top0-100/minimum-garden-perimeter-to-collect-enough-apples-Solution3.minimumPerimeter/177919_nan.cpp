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


    long long minimumPerimeter(long long neededApples) {
        // 2r  , 2r-1, ..., r+1, r  , r+1, ..., 2*r-1, 2*r
        // 2r-1,                 r-1,                  2r-1
        // .                     .                     .    
        // .                     .                     .    
        // .                     .                     .    
        // r+1 ,    r, ...,   2, 1  ,   2, ...,   r  , r+1
        // r   ,  r-1, ...,   1, 0  ,   1, ...,   r-1, r
        // r+1 ,    r, ...,   2, 1  ,   2, ...,   r  , r+1
        // .                     .                     .    
        // .                     .                     .    
        // .                     .                     .    
        // 2r-1,                 r-1,                  2r-1
        // 2r  , 2r-1, ..., r+1, r  , r+1, ..., 2*r-1, 2*r
        //
        // the sum of each row/col forms an arithmetic sequence
        // => let ai = (((r + (r-1) + ... + r + 0) + (0 + 1 + 2 + ... + r)) - 0) + i*(2r+1)
        //           = (2*(0+r)*(r+1)/2-0) + i*(2r+1)
        //           = r*(r+1) + i*(2r+1)
        // => total  = 2*(a0 + a1 + ... ar) - a0
        //           = 2*(r*(r+1) + r*(r+1) + r*(2r+1)))*(r+1)/2 - r*(r+1)
        //           = r*(4r+3)*(r+1)-r*(r+1)
        //           = 4r^3+6r^2+2r
        // => find min r, s.t. 4r^3+6r^2+2r >= neededApples

        int64_t left = 1, right = pow(neededApples / 4.0, 1.0 / 3);
        while (left <= right) {
            const auto& mid = left + (right - left) / 2;
            if (check(neededApples, mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return 8 * left;
    }


