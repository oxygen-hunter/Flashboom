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

    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        int max_f = *max_element(cbegin(forbidden), cend(forbidden));
        int max_val = (a >= b) ? x + b : max(x, max_f) + a + b;  // a may be a non-periodic area, (a+b) is a periodic area which is divided by gcd(a, b) and all points are reachable
        vector<unordered_set<int>> lookup(2); 
        for (const auto& pos : forbidden) {
            lookup[0].emplace(pos);
            lookup[1].emplace(pos);
        }
        int result = 0;
        vector<pair<int, int>> q = {{0, true}};
        lookup[0].emplace(0);
        while (!empty(q)) {
            vector<pair<int, int>> new_q;
            for (const auto& [pos, can_back] : q) {
                if (pos == x) {
                    return result;
                }
                if (pos + a <= max_val && !lookup[0].count(pos + a)) {
                    lookup[0].emplace(pos + a);
                    new_q.emplace_back(pos + a, true);
                }
                if (!can_back) {
                    continue;
                }
                if (pos - b >= 0 && !lookup[1].count(pos - b)) {
                    lookup[1].emplace(pos - b);
                    new_q.emplace_back(pos - b, false);
                }
            }
            q = move(new_q);
            ++result;
        }
        return -1;
    }

