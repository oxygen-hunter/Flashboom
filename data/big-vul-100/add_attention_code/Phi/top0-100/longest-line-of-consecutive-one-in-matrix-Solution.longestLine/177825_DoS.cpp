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

    int longestLine(vector<vector<int>>& M) {
        if (M.empty()) {
            return 0;
        }
        int result = 0;
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(M[0].size(), vector<int>(4)));
        for (int i = 0; i < M.size(); ++i) {
            for (int j = 0; j < M[0].size(); ++j) {
                dp[i % 2][j][0] = dp[i % 2][j][1] = dp[i % 2][j][2] = dp[i % 2][j][3] = 0;
                if (M[i][j] == 1) {
                    dp[i % 2][j][0] = j > 0 ? dp[i % 2][j - 1][0] + 1 : 1;
                    dp[i % 2][j][1] = i > 0 ? dp[(i - 1) % 2][j][1] + 1 : 1;
                    dp[i % 2][j][2] = (i > 0 && j > 0) ? dp[(i - 1) % 2][j - 1][2] + 1 : 1;
                    dp[i % 2][j][3] = (i > 0 && j < M[0].size() - 1) ? dp[(i - 1) % 2][j + 1][3] + 1 : 1;
                    result = max(result, max(dp[i % 2][j][0], max(dp[i % 2][j][1], max(dp[i % 2][j][2], dp[i % 2][j][3]))));
                }
            }
        }
        return result;
    }

