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


    vector<int> getGoodIndices(vector<vector<int>>& variables, int target) {
        const auto& addmod = [&](uint32_t a, uint32_t b, uint32_t mod) {  // avoid overflow
            a %= mod, b %= mod;
            if (mod - a <= b) {
                b -= mod;  // relied on unsigned integer overflow in order to give the expected results
            }
            return a + b;
        };

        const auto& mulmod = [&](uint32_t a, uint32_t b, uint32_t mod)  {  // avoid overflow
            a %= mod, b %= mod;
            uint32_t result = 0;
            if (a < b) {
                swap(a, b);
            }
            while (b > 0)  { 
                if (b % 2 == 1) {
                    result = addmod(result, a, mod);
                }
                a = addmod(a, a, mod);
                b /= 2; 
            } 
            return result; 
        };

        const auto& powmod = [&](uint32_t a, uint32_t b, uint32_t mod) {
            a %= mod;
            uint32_t result = 1;
            while (b) {
                if (b & 1) {
                    result = mulmod(result, a, mod);
                }
                a = mulmod(a, a, mod);
                b >>= 1;
            }
            return result;
        };

        vector<int> result;
        for (int i = 0; i < size(variables); ++i) {
            if (powmod(powmod(variables[i][0], variables[i][1], 10), variables[i][2], variables[i][3]) == target) {
                result.emplace_back(i);
            }
        }
        return result;
    }


