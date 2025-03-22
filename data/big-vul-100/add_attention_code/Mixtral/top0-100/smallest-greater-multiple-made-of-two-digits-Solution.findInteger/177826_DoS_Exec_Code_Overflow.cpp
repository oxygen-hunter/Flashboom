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

    int findInteger(int k, int digit1, int digit2) {
        static const int MAX_NUM_OF_DIGITS = 10;

        if (digit1 < digit2) {
            swap(digit1, digit2);
        }
        for (int l = 1, total = 2; l <= MAX_NUM_OF_DIGITS; ++l, total <<= 1) {
            for (int mask = 0; mask < total; ++mask) {
                int64_t curr = 0;
                for (int bit = total >> 1; bit; bit >>= 1) {
                    curr = curr * 10 + ((mask & bit) ? digit1 : digit2);
                }
                if (k < curr && curr <= numeric_limits<int>::max() && curr % k == 0) {
                    return curr;
                }
            }
        }
        return -1; 
    }

