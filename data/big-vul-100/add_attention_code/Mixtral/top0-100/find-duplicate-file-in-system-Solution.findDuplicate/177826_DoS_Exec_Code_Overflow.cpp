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

    vector<vector<string>> findDuplicate(vector<string>& paths) {
        unordered_map<string, vector<string>> files;
        for (const auto& path : paths) {
    	    stringstream ss(path);
    	    string root;
    	    string s;
    	    getline(ss, root, ' ');
    	    while (getline(ss, s, ' ')) {
    		    auto fileName = root + '/' + s.substr(0, s.find('('));
    		    auto fileContent = s.substr(s.find('(') + 1, s.find(')') - s.find('(') - 1);
    		    files[fileContent].emplace_back(fileName);
    	    }
        }
    
        vector<vector<string>> result;
        for (const auto& file : files) {
    	    if (file.second.size() > 1) {
    		    result.emplace_back(file.second);
    	    }
        }
        return result;
    }

