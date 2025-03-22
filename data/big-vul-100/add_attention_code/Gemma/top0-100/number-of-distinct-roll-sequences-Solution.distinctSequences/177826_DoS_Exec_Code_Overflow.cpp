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


    int distinctSequences(int n) {
        static const int MOD = 1e9 + 7;
        if (n == 1) {
            return 6;
        }
        vector<vector<int>> dp(6, vector<int>(6));
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                if (i != j && gcd(i + 1, j + 1) == 1) {
                    dp[i][j] = 1;
                }
            }
        }
        for (int _ = 0; _ < n - 2; ++_) {
            vector<vector<int>> new_dp(6, vector<int>(6));
            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 6; ++j) {
                    if (!dp[i][j]) {
                        continue;
                    }
                    for (int k = 0; k < 6; ++k) {
                        if (!dp[j][k]) {
                            continue;
                        }
                        if (k != i) {
                            new_dp[i][j] = (new_dp[i][j] + dp[j][k]) % MOD;
                        }
                    }
                }
            }
            dp = move(new_dp);
        }
        return accumulate(cbegin(dp), cend(dp), 0,
                          [&](int total, const auto& x) {
                              return (total + accumulate(cbegin(x), cend(x), 0,
                                                         [&](int total, int x) {
                                                             return (total + x) % MOD;
                                                         })) % MOD;
                          });
    }


