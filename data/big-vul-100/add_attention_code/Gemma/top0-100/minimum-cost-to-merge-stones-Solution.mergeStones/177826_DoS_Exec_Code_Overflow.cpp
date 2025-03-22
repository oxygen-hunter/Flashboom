 bool extractPages (const char *srcFileName, const char *destFileName) {
  char pathName[1024];
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
    firstPage = 1;
  if (firstPage != lastPage && strstr(destFileName, "%d") == NULL) {
    error(errSyntaxError, -1, "'{0:s}' must contain '%%d' if more than one page should be extracted", destFileName);
     return false;
   }
   for (int pageNo = firstPage; pageNo <= lastPage; pageNo++) {
    sprintf (pathName, destFileName, pageNo);
     GooString *gpageName = new GooString (pathName);
     int errCode = doc->savePageAs(gpageName, pageNo);
     if ( errCode != errNone) {
      delete gpageName;
      delete gfileName;
      return false;
    }
    delete gpageName;
  }
  delete gfileName;
  return true;
}


    int mergeStones(vector<int>& stones, int K) {
        if ((stones.size() - 1) % (K - 1)) {
            return -1;
        }
        vector<int> prefix(stones.size() + 1, 0);
        partial_sum(cbegin(stones), cend(stones), next(begin(prefix)), plus<int>());

        vector<vector<int> > dp(stones.size(), vector<int>(stones.size()));
        for (int l = K - 1; l < stones.size(); ++l) {
            for (int i = 0; i + l < stones.size(); ++i) {
                dp[i][i + l] = numeric_limits<int>::max();
                for (int j = i; j + 1 <= i + l; j += K - 1) {
                    dp[i][i + l] = min(dp[i][i + l], dp[i][j] + dp[j + 1][i + l]);
                }
                if (l % (K - 1) == 0) {
                    dp[i][i + l] += prefix[i + l + 1] - prefix[i];
                }
            }
        }
        return dp[0][stones.size() - 1];
    }


