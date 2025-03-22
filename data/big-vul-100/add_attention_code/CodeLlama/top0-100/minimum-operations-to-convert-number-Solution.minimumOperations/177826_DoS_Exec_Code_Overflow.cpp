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


    int minimumOperations(vector<int>& nums, int start, int goal) {
        static const int MAX_X = 1000;

        vector<int> new_nums;
        for (const auto& y : nums) {
            if (y && ((0 <= y && y <= MAX_X) || (0 <= (goal - y) && (goal - y) <= MAX_X) || (0 <= (goal + y) && (goal + y) <= MAX_X) || (0 <= (goal ^ y) && (goal ^ y) <= MAX_X))) {
                new_nums.emplace_back(y);
            }
        }
        nums = move(new_nums);
        vector<pair<int, int>> q = {{start, 0}};
        unordered_set<int> lookup = {start};
        while (!empty(q)) {
            vector<pair<int, int>> new_q;
            for (const auto& [x, steps] : q) {
                for (const auto& y : nums) {
                    for (const auto& nx : {x + y, x - y, x ^ y}) {
                        if (nx == goal) {
                            return steps + 1;
                        }
                        if (!(0 <= nx && nx <= MAX_X) || lookup.count(nx)) {
                            continue;
                        }
                        lookup.emplace(nx);
                        new_q.emplace_back(nx, steps + 1);
                    }
                }
            }
            q = move(new_q);
        }
        return -1;
    }


