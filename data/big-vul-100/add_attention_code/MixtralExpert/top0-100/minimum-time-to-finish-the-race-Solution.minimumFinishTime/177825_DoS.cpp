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


    int minimumFinishTime(vector<vector<int>>& tires, int changeTime, int numLaps) {
        static const int INF = numeric_limits<int>::max();

        const auto& ceil_log2 = [](const auto& x) {
            return std::__lg(x - 1) + 1;
        };
        vector<int64_t> dp(ceil_log2(changeTime + 1), INF);  // dp[i]: min time to complete i+1 laps without changing a tire
        for (int i = 0; i < size(tires); ++i) {
            const int f = tires[i][0], r = tires[i][1];
            for (int64_t curr = f, total = f, cnt = 0;
                 curr < changeTime + f;
                 curr *= r, total += curr, ++cnt) {  // at worst (f, r) = (1, 2) => 2^(cnt-1) < changeTime+1 => cnt < ceil(log2(changeTime+1))
                dp[cnt] = min(dp[cnt], total);
            }
        }
        vector<int64_t> dp2(numLaps, INF);  // dp2[i]: min time to complete i+1 laps with changing zero or more tires
        for (int i = 0; i < numLaps; ++i) {
            for (int j = 0; j < min(i + 1, static_cast<int>(size(dp))); ++j) {
                dp2[i] = min(dp2[i], (i - j - 1 >= 0 ? dp2[i - j - 1] + changeTime : 0) + dp[j]);
            }
        }
        return dp2.back();
    }


