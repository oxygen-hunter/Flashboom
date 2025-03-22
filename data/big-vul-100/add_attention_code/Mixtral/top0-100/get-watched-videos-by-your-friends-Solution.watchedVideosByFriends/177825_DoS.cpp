bool extractPages (const char *srcFileName, const char *destFileName) {
  char pathName[4096];
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
   if (firstPage == 0)
     firstPage = 1;
   if (firstPage != lastPage && strstr(destFileName, "%d") == NULL) {
    error(errSyntaxError, -1, "'{0:s}' must contain '%%d' if more than one page should be extracted", destFileName);
     return false;
   }
   for (int pageNo = firstPage; pageNo <= lastPage; pageNo++) {
     snprintf (pathName, sizeof (pathName) - 1, destFileName, pageNo);
     GooString *gpageName = new GooString (pathName);
	{
	  printUsage ("pdfseparate", "<PDF-sourcefile> <PDF-pattern-destfile>",
		      argDesc);
	}
      if (printVersion || printHelp)
	exitCode = 0;
      goto err0;
    }
  globalParams = new GlobalParams();
  ok = extractPages (argv[1], argv[2]);
  if (ok) {
    exitCode = 0;
  }
  delete globalParams;

err0:

  return exitCode;
}

    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {
        vector<int> curr_level = {id};
        unordered_set<int> lookup = {id};
        for (int i = 0; i < level; ++i) {
            vector<int> new_level;
            for (const auto& i : curr_level) {
                for (const auto& j : friends[i]) {
                    if (lookup.count(j)) {
                        continue;
                    }
                    lookup.emplace(j);
                    new_level.emplace_back(j);
                }
            }
            curr_level = move(new_level);
        }

        unordered_map<string, int> count;
        for (const auto& i : curr_level) {
            for (const auto& v : watchedVideos[i]) {
                ++count[v];
            }
        }
        vector<string> result;
        transform(count.cbegin(), count.cend(), back_inserter(result),
                  [](const auto& x) {
                      return x.first;
                  });
        sort(result.begin(), result.end(),
             [&count](const auto& a, const auto& b) {
                 return make_pair(count[a], a) < make_pair(count[b], b);
             });
        return result;
    }

