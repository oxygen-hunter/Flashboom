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

    long long maxBalancedSubsequenceSum(vector<int>& nums) {
        static const auto NEG_INF = numeric_limits<int64_t>::min();

        unordered_set<int> vals_set;
        for (int i = 0; i < size(nums); ++i) {
            vals_set.emplace(nums[i] - i);
        }
        vector<int> sorted_vals(cbegin(vals_set), cend(vals_set));
        sort(begin(sorted_vals), end(sorted_vals));
        unordered_map<int, int> val_to_idx;
        for (int i = 0; i < size(sorted_vals); ++i) {
            val_to_idx[sorted_vals[i]] = i;
        }
        SegmentTree<int64_t> st(size(val_to_idx));
        for (int i = 0; i < size(nums); ++i) {
            const auto val = max(st.query(0, val_to_idx[nums[i] - i]), static_cast<int64_t>(0)) + nums[i];
            st.update(val_to_idx[nums[i] - i], val);
        }
        return st.query(0, size(val_to_idx) - 1);
    }

