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


    bool wordPattern(string pattern, string str) {
        // Count the words.
        int cnt = str.empty() ? 0 : 1;
        for (const auto& c : str) {
            if (c == ' ') {
                ++cnt;
            }
        }
        if (pattern.size() != cnt) {
            return false;
        }

        unordered_map<string, char> w2p;
        unordered_map<char, string> p2w;
        int i = 0, j = 0;
        for (const auto& p : pattern) {
            // Get a word at a time without saving all the words.
            j = str.find(" ", i);
            if (j == string::npos) {
                j = str.length();
            }
            const string w = str.substr(i, j - i);
    
            if (!w2p.count(w) && !p2w.count(p)) { 
                // Build mapping. Space: O(c)
                w2p[w] = p; 
                p2w[p] = w; 
            } else if (!w2p.count(w) || w2p[w] != p) {
                // Contradict mapping.
                return false;
            }
            i = j + 1;
        }
        return true;
    }


