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

    vector<int> pathsWithMaxScore(vector<string>& board) {
        static const int MOD = 1e9 + 7;
        static const vector<pair<int, int>> directions{{1, 0}, {0, 1}, {1, 1}};
        
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(board[0].size() + 1, vector<int>(2)));
        dp[(board.size() - 1) % 2][board[0].size() - 1] = {0, 1};
        for (int r = board.size() - 1; r >= 0; --r) {
            for (int c = board[0].size() - 1; c >= 0; --c) {
                if (board[r][c] == 'S' || board[r][c] == 'X') {
                    continue;
                }
                dp[r % 2][c] = {0, 0};
                for (const auto& [dr, dc] : directions) {
                    if (dp[r % 2][c][0] < dp[(r + dr) % 2][c + dc][0]) {
                        dp[r % 2][c] = dp[(r + dr) % 2][c + dc];
                    } else if (dp[r % 2][c][0] == dp[(r + dr) % 2][c + dc][0]) {
                        dp[r % 2][c][1] = (dp[r % 2][c][1]+dp[(r + dr) % 2][c + dc][1]) % MOD;
                    }
                }
                if (dp[r % 2][c][1] && board[r][c] != 'E') {
                    dp[r % 2][c][0] += board[r][c] - '0';
                }
            }
        }
        return dp[0][0];
    }

