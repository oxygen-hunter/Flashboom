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


    string reorderSpaces(string text) {
        // count spaces and words
        int space_count = 0, word_count = 0;
        for (int i = 0; i < size(text); ++i) {
            if (text[i] == ' ') {
                ++space_count;
            } else if (i == 0 || text[i - 1] == ' ') {
                ++word_count;
            }
        }
        // rearrange the spaces to the right
        int left = 0, curr = 0;
        for (int i = 0; i < size(text); ++i) {
            bool has_word = false;
            while (i < size(text) && text[i] != ' ') {
                swap(text[left++], text[i++]);
                has_word = true;
            }
            if (has_word) {
                ++left;  // keep one space
            }
        }
        // rearrange the spaces to the left
        int equal_count = word_count - 1 > 0 ? space_count / (word_count - 1) : 0;
        int extra_count = word_count - 1 > 0 ? space_count % (word_count - 1) : space_count;
        int right = size(text) - 1 - extra_count;
        for (int i = size(text) - 1; i >= 0; --i) {
            bool has_word = false;
            while (i >= 0 && text[i] != ' ') {
                swap(text[right--], text[i--]);
                has_word = true;
            }
            if (has_word) {
                right -= equal_count;  // keep equal_count spaces
            }
        }
        return text;
    }


