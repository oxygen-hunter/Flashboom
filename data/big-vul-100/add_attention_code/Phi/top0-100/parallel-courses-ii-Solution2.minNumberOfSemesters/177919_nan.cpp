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

    int minNumberOfSemesters(int n, vector<vector<int>>& dependencies, int k) {
        static const auto& choice_mask =
            [](const auto& nums, const auto& idxs) {
                return accumulate(cbegin(idxs), cend(idxs), 0,
                                  [&nums](const auto& a, const auto& b) {
                                      return a | (1 << nums[b]);
                                  });
            };
        static const auto& next_pos =
            [](const auto& n, const auto& r, const auto& idxs) {
                int i = r - 1;
                for (; i >= 0; --i) {
                    if (idxs[i] != i + n - r) {
                        break;
                    }
                }
                return i;
            };

        vector<int> reqs(n);
        for (const auto& d : dependencies) {
            reqs[d[1] - 1] |= 1 << (d[0] - 1);
        }
        vector<int> dp(1 << n, n);
        dp[0] = 0;
        for (int mask = 0; mask < dp.size(); ++mask) {
            vector<int> candidates;
            for (int v = 0; v < n; ++v) {
                if ((mask & (1 << v)) == 0 && (mask & reqs[v]) == reqs[v]) {
                    candidates.emplace_back(v);
                }
            }
            const auto r = min(int(candidates.size()), k);
            vector<int> idxs(r);
            iota(begin(idxs), end(idxs), 0);
            const auto& new_mask = (mask | choice_mask(candidates, idxs));
            dp[new_mask] = min(dp[new_mask], dp[mask] + 1);
            for (int i; (i = next_pos(candidates.size(), r, idxs)) >= 0;) {
                ++idxs[i];
                for (int j = i + 1; j < k; ++j) {
                    idxs[j] = idxs[j - 1] + 1;
                }
                const auto& new_mask = (mask | choice_mask(candidates, idxs));
                dp[new_mask] = min(dp[new_mask], dp[mask] + 1);
            }
        }
        return dp.back();
    }

