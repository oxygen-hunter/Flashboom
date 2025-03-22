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

    int maxSumMinProduct(vector<int>& nums) {
        static const int MOD = 1e9 + 7;

        vector<int64_t> prefix(nums.size() + 1);
        for (int i = 0; i < size(nums); ++i) {
           prefix[i + 1] = prefix[i] + nums[i];
        }
        vector<int> stk = {-1};
        int64_t result = 0;
        for (int i = 0; i <= size(nums); ++i) {
            while (stk.back() != -1 && (i == size(nums) || nums[stk.back()] >= nums[i])) {
                int j = stk.back();
                stk.pop_back();
                result = max(result, nums[j] * (prefix[(i - 1) + 1] - prefix[stk.back() + 1]));
            }
            stk.emplace_back(i);
        }
        return result % MOD;
    }

