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

    string oddString(vector<string>& words) {
        for (int i = 0; i < size(words[0]) - 1; ++i) {
            unordered_map<int, vector<int>> lookup;
            for (int j = 0; j < size(words); ++j) {
                if (size(lookup[words[j][i + 1] - words[j][i]]) < 2) {
                    lookup[words[j][i + 1] - words[j][i]].emplace_back(j);
                }
            }
            if (size(lookup) == 2) {
                return size(cbegin(lookup)->second) == 1
                       ? words[cbegin(lookup)->second[0]]
                       : words[next(cbegin(lookup))->second[0]];
            }
        }
        return "";
    }

