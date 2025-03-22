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


        vector<vector<string> > partition(string s) {
            const int n = s.size();
            bool p[n][n];

            fill_n(&p[0][0], n * n, false);

            for (int i = n - 1; i >= 0; --i)
                for (int j = i; j < n; ++j)
                    p[i][j] = s[i] == s[j] && ((j - i < 2) || p[i + 1][j - 1]);

            vector<vector<string> > sub_palins[n];
            for (int i = n - 1; i >= 0; --i) {
                for (int j = i; j < n; ++j)
                    if (p[i][j]) {
                        const string palindrome = s.substr(i, j - i + 1);
                        if (j + 1 < n) {
                            for (auto v : sub_palins[j + 1]) {
                                v.insert(v.begin(), palindrome);
                                sub_palins[i].push_back(v);
                            }
                        } 
                        else {
                            sub_palins[i].push_back(vector<string> { palindrome });
                        }
                    }
            }

            return sub_palins[0];
        }


