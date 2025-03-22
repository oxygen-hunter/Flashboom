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

    int maxMoves(int kx, int ky, vector<vector<int>>& positions) {
        static const int N = 50;
        static const vector<pair<int, int>> DIRECTIONS = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};
        static const int POS_INF = numeric_limits<int>::max();
        static const int NEG_INF = numeric_limits<int>::min();

        const auto& bfs = [](int r, int c) {
            vector<vector<int>> dist(N, vector<int>(N, POS_INF));
            dist[r][c] = 0;
            vector<pair<int, int>> q = {{r, c}};
            while (!empty(q)) {
                vector<pair<int, int>> new_q;
                for (const auto& [r, c] : q) {
                    for (const auto& [dr, dc] : DIRECTIONS) {
                        const int nr = r + dr, nc = c + dc;
                        if (!(0 <= nr && nr < N && 0 <= nc && nc < N && dist[nr][nc] == POS_INF)) {
                            continue;
                        }
                        dist[nr][nc] = dist[r][c] + 1;
                        new_q.emplace_back(nr, nc);
                    }
                }
                q = move(new_q);
            }
            return dist;
        };

        const int p = size(positions);
        positions.emplace_back(vector<int>{kx, ky});
        vector<vector<int>> dist(p + 1, vector<int>(p + 1));
        for (int i = 0; i <= p; ++i) {
            const auto& d = bfs(positions[i][0], positions[i][1]);
            for (int j = i + 1; j <= p; ++j) {
                dist[j][i] = dist[i][j] = d[positions[j][0]][positions[j][1]];
            }
        }
        vector<vector<int>> dp(1 << p);
        for (int mask = 1; mask < 1 << p; ++mask) {
            dp[mask].assign(p, __builtin_popcount(mask) & 1 ? POS_INF : NEG_INF);
        }
        dp.back().assign(p, 0);
        for (int mask = (1 << p) - 1; mask >= 1; --mask) {
            const auto& turn = (__builtin_popcount(mask) & 1) ^ 1;
            for (int i = 0; i < p; ++i) {
                if ((mask & (1 << i)) == 0) {
                    continue;
                }
                for (int j = 0; j < p; ++j) {
                    if (j == i || (mask & (1 << j)) == 0) {
                        continue;
                    }
                    dp[mask ^ (1 << i)][j] = turn ? min(dp[mask ^ (1 << i)][j], dp[mask][i] + dist[i][j])
                                                  : max(dp[mask ^ (1 << i)][j], dp[mask][i] + dist[i][j]);
                }
            }
        }
        int result = 0;
        for (int i = 0; i < p; ++i) {
            result = max(result, dp[1 << i][i] + dist[i][p]);
        }
        return result;
    }

