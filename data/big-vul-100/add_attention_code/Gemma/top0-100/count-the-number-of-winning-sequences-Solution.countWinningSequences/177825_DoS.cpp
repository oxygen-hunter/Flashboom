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


    int countWinningSequences(string s) {
        static const int MOD = 1e9 + 7;
        static const unordered_map<char, int> lookup = {{'F', 0}, {'W', 1}, {'E', 2}};

        vector<unordered_map<int, int>> dp(3);
        for (int i = 0; i < size(s); ++i) {
            vector<unordered_map<int, int>> new_dp(3);
            const auto x = lookup.at(s[i]);
            for (int j = 0; j < 3; ++j) {
                const int diff = ((j - x + 1) % 3 + 3) % 3 - 1;
                if (i == 0) {
                    new_dp[j][diff] = 1;
                    continue;
                }
                for (int k = 0; k < 3; ++k) {
                    if (k == j) {
                        continue;
                    }
                    for (const auto& [v, c] : dp[k]) {
                        new_dp[j][v + diff] = (new_dp[j][v + diff] + c) % MOD;
                    }
                }
            }
            dp = move(new_dp);
        }
        int result = 0;
        for (int j = 0; j < 3; ++j) {
            for (const auto& [v, c] : dp[j]) {
                if (v >= 1) {
                    result = (result + c) % MOD;
                }
            }
        }
        return result;
    }


