char **XGetFontPath(
    register Display *dpy,
    int *npaths)	/* RETURN */
{
	xGetFontPathReply rep;
	unsigned long nbytes = 0;
	char **flist = NULL;
	char *ch = NULL;
	char *chend;
	int count = 0;
	register unsigned i;
	register int length;
	_X_UNUSED register xReq *req;

	LockDisplay(dpy);
	GetEmptyReq (GetFontPath, req);
	(void) _XReply (dpy, (xReply *) &rep, 0, xFalse);

	if (rep.nPaths) {
	    flist = Xmalloc(rep.nPaths * sizeof (char *));
	    if (rep.length < (INT_MAX >> 2)) {
		nbytes = (unsigned long) rep.length << 2;
		ch = Xmalloc (nbytes + 1);
                /* +1 to leave room for last null-terminator */
	    }

	    if ((! flist) || (! ch)) {
		Xfree(flist);
		Xfree(ch);
		_XEatDataWords(dpy, rep.length);
		UnlockDisplay(dpy);
		SyncHandle();
		return (char **) NULL;
	    }

	    _XReadPad (dpy, ch, nbytes);
 	    /*
 	     * unpack into null terminated strings.
 	     */
	    chend = ch + (nbytes + 1);
 	    length = *ch;
 	    for (i = 0; i < rep.nPaths; i++) {
 		if (ch + length < chend) {
		    flist[i] = ch+1;  /* skip over length */
		    ch += length + 1; /* find next length ... */
		    length = *ch;
		    *ch = '\0'; /* and replace with null-termination */
		    count++;
		} else
		    flist[i] = NULL;
	    }
	}
	*npaths = count;
	UnlockDisplay(dpy);
	SyncHandle();
	return (flist);
}


    string largestPalindrome(int n, int k) {
        const auto& powmod = [](uint32_t a, uint32_t b, uint32_t mod) {
            a %= mod;
            uint64_t result = 1;
            while (b) {
                if (b & 1) {
                    result = result * a % mod;
                }
                a = uint64_t(a) * a % mod;
                b >>= 1;
            }
            return result;
        };

        const auto& inv = [&](int x, int p) {
            return powmod(x, p - 2, p);
        };

        const auto& f = [&](int l) {
            static const int p = 7;
            string result(l, '9');
            if (l == 0) {
                return result;
            }
            int curr = 0;
            for (const auto& x : result) {
                curr = (curr * 10 + (x - '0')) % p;
            }
            // l%2 == 0: (curr+(i-9)*11*pow(10, l//2-1, p))%p = 0
            // l%2 == 1: (curr+(i-9)*pow(10, l//2, p))%p = 0
            int i = 9 - (curr * inv(l % 2 == 0 ? 11 : 1, p) * inv(powmod(10, l / 2 - (l % 2 == 0 ? 1 : 0), p), p)) % p;
            if (i <= 2) {
                i += p;
            }
            result[l / 2] = result[l / 2 - (l % 2 == 0 ? 1 : 0)] = '0' + i;
            return result;
        };

        if (k == 1 || k == 3 || k == 9) {
            return string(n, '9');
        }
        if (k == 2 || k == 4 || k == 8) {
            k = min(k, 6);
            if (n <= k) {
                return string(n, '8');
            }
            const int l = k / 2;
            return string(l, '8') + string(n - k, '9') + string(l, '8');
        }
        if (k == 5) {
            if (n <= 2) {
                return string(n, '5');
            }
            return string(1, '5') + string(n - 2, '9') + string(1, '5');
        }
        if (k == 6) {
            if (n <= 2) {
                return string(n, '6');
            }
            if (n % 2) {
                const int l = n / 2 - 1;
                return string(1, '8') + string(l, '9') + string(1, '8') + string(l, '9') + string(1, '8');
            }
            const int l = n / 2 - 2;
            return string(1, '8') + string(l, '9') + string(2, '7') + string(l, '9') + string(1, '8');
        }
        const int l = n / 12, r = n % 12;
        return string(l * 6, '9') + f(r) + string(l * 6, '9');  // 999999%7 = 0
    }


