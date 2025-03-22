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

    int slidingPuzzle(vector<vector<int>>& board) {
        const auto& R = board.size(), &C = board[0].size();
        vector<int> begin, end;
        unordered_map<int, pair<int, int>> expected;
        int zero_idx = 0;
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                auto val = (C * i + j + 1) % (R * C);
                expected[val] = {i, j};
                if (board[i][j] == 0) {
                    zero_idx = begin.size();
                }
                begin.emplace_back(board[i][j]);
                end.emplace_back(val);
            }
        }
        vector<int> end_wrong(end);
        swap(end_wrong[end_wrong.size() - 2], end_wrong[end_wrong.size() - 3]);
           
        using P = tuple<int, int, int, vector<int>>;
        priority_queue<P, vector<P>, greater<P>> min_heap;
        min_heap.emplace(make_tuple(0, 0, zero_idx, begin));
        unordered_map<vector<int>, int, Hash<vector<int>>> lookup;
        lookup[begin] = 0;
        while (!min_heap.empty()) {
            int f, g, zero;
            vector<int> board;
            tie(f, g, zero, board) = min_heap.top(); min_heap.pop();
            if (board == end) {
                return g;
            }
            if (board == end_wrong) {
                return -1;
            }
            if (f > lookup[board]) {
                continue;
            }
            int r = zero / C;
            int c = zero % C;
            static const vector<pair<int, int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            for (const auto& direction : directions) {
                int i = r + direction.first;
                int j = c + direction.second;
                if (0 <= i && i < R && 0 <= j && j < C) {
                    auto new_zero = C * i + j;
                    auto new_board = board;
                    swap(new_board[zero], new_board[new_zero]);
                    f = g + 1 + heuristic_estimate(new_board, R, C, expected);
                    if (!lookup.count(new_board) || f < lookup[new_board])
                        lookup[new_board] = f;
                        min_heap.emplace(make_tuple(f, g + 1, new_zero, new_board));
                    }
                }
            }
        }

