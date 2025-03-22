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

    int sumOfFlooredPairs(vector<int>& nums) {
        static const int MOD = 1e9 + 7;
        vector<int> prefix(*max_element(cbegin(nums), cend(nums)) + 1);
        unordered_map<int, int> count;
        for (const auto& num : nums) {
            ++count[num];
        }
        for (const auto& [num, cnt] : count) {
            for (int j = num; j < size(prefix); j += num) {
                prefix[j] += cnt;
            }
        }
        for (int i = 0; i + 1 < size(prefix); ++i) {
            prefix[i + 1] += prefix[i];
        }
        return accumulate(cbegin(nums), cend(nums), 0,
                          [&prefix](int total, int x) {
                              return (total + prefix[x]) % MOD;
                          });
    }

