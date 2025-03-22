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

    int seat() {
        while (!seats_.count(max_heap_.top().first) ||
               !seats_.count(max_heap_.top().second) ||
               seats_[max_heap_.top().first].second != max_heap_.top().second ||
               seats_[max_heap_.top().second].first != max_heap_.top().first) {
            max_heap_.pop();  // lazy deletion
        }
        
        const auto top = max_heap_.top(); max_heap_.pop();
        const auto& mid = top.first == -1 ? 0
                          : top.second == num_ ? num_ - 1
                          : (top.first + top.second) / 2;
        seats_[mid] = top;
        seats_[top.first].second = mid;
        seats_[top.second].first = mid;
        max_heap_.emplace(top.first, mid);
        max_heap_.emplace(mid, top.second);
        return mid;
    }

