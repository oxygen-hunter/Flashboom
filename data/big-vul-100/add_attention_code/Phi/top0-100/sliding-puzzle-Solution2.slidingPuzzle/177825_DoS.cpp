bool extractPages (const char *srcFileName, const char *destFileName) {
  char pathName[4096];
  GooString *gfileName = new GooString (srcFileName);
  PDFDoc *doc = new PDFDoc (gfileName, NULL, NULL, NULL);

  if (!doc->isOk()) {
    error(errSyntaxError, -1, "Could not extract page(s) from damaged file ('{0:s}')", srcFileName);
    return false;
  }

  if (firstPage == 0 && lastPage == 0) {
    firstPage = 1;
    lastPage = doc->getNumPages();
  }
  if (lastPage == 0)
    lastPage = doc->getNumPages();
  if (firstPage == 0)
   if (firstPage == 0)
     firstPage = 1;
   if (firstPage != lastPage && strstr(destFileName, "%d") == NULL) {
    error(errSyntaxError, -1, "'{0:s}' must contain '%%d' if more than one page should be extracted", destFileName);
     return false;
   }
   for (int pageNo = firstPage; pageNo <= lastPage; pageNo++) {
     snprintf (pathName, sizeof (pathName) - 1, destFileName, pageNo);
     GooString *gpageName = new GooString (pathName);
	{
	  printUsage ("pdfseparate", "<PDF-sourcefile> <PDF-pattern-destfile>",
		      argDesc);
	}
      if (printVersion || printHelp)
	exitCode = 0;
      goto err0;
    }
  globalParams = new GlobalParams();
  ok = extractPages (argv[1], argv[2]);
  if (ok) {
    exitCode = 0;
  }
  delete globalParams;

err0:

  return exitCode;
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

