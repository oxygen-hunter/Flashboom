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
	    chend = ch + (rlen + 1);
 	    length = *ch;
 	    for (i = 0; i < rep.nExtensions; i++) {
 		if (ch + length < chend) {
 		    list[i] = ch+1;  /* skip over length */
 		    ch += length + 1; /* find next length ... */
		    if (ch <= chend) {
			length = *ch;
			*ch = '\0'; /* and replace with null-termination */
			count++;
		    } else {
			list[i] = NULL;
		    }
 		} else
 		    list[i] = NULL;
 	    }
		    }
		} else

    int minimumDifference(vector<int>& nums) {
        vector<int> left, right; 
        for (int i = 0; i < size(nums); ++i) {
            if (i < size(nums) / 2) {
                left.emplace_back(nums[i]); 
            } else {
                right.emplace_back(nums[i]); 
            }
        }
        const auto& total1 = accumulate(cbegin(left), cend(left), 0);
        const auto& total2 = accumulate(cbegin(right), cend(right), 0);
        const int bound = (1 << size(left));
        unordered_map<int, vector<int>> sums;
        for (int mask = 0; mask < bound; ++mask) {
            int total = 0, bit = 1;
            for (const auto& x : left) {
                if (mask & bit) {
                    total += x; 
                }
                bit <<= 1;
            }
            sums[__builtin_popcount(mask)].emplace_back(2 * total - total1); 
        }
        for (auto& [_, v] : sums) {
            sort(begin(v), end(v));
        }
        int result = numeric_limits<int>::max();
        for (int mask = 0; mask < bound; ++mask) {
            int total = 0, bit = 1;
            for (const auto& x : right) {
                if (mask & bit) {
                    total += x; 
                }
                bit <<= 1;
            }
            const int k = size(right) - __builtin_popcount(mask);
            const int diff = 2 * total - total2; 
            const auto cit = lower_bound(cbegin(sums[k]), cend(sums[k]), -diff); 
            if (cit != cend(sums[k])) {
                result = min(result, abs(*cit + diff)); 
            }
            if (cit != cbegin(sums[k])) {
                result = min(result, abs(*prev(cit) + diff));    
            }
        }
        return result; 
    }

