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


    vector<long long> countBlackBlocks(int m, int n, vector<vector<int>>& coordinates) {
        static const int L = 2;
    
        unordered_map<int64_t, int> cnt;
        for (const auto& c : coordinates) {
            const int x = c[0], y = c[1];
            for (int nx = max(x - (L - 1), 0); nx < min(x + 1, m - (L - 1)); ++nx) {
                for (int ny = max(y - (L - 1), 0); ny < min(y + 1, n - (L - 1)); ++ny) {
                    ++cnt[static_cast<int64_t>(nx) * n + ny];
                }
            }
        }
        vector<long long> result(L * L + 1);
        for (const auto& [_, c] : cnt) {
            ++result[c];
        }
        result[0] = static_cast<int64_t>(m - (L - 1)) * (n - (L - 1)) - accumulate(cbegin(result) + 1, cend(result), 0ll);
        return result;
    }


