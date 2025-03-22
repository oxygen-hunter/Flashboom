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

    int catMouseGame(vector<vector<int>>& graph) {
        vector<vector<vector<int>>> degree(size(graph), vector<vector<int>>(size(graph), vector<int>(2)));
        unordered_set<int> ignore(cbegin(graph[HOLE]), cend(graph[HOLE]));
        for (int m = 0; m < size(graph); ++m) {
            for (int c = 0; c < size(graph); ++c) {
                degree[m][c][MOUSE - 1] = size(graph[m]);
                degree[m][c][CAT - 1] = size(graph[c]) - ignore.count(c);
            }
        }
        vector<vector<vector<int>>> color(size(graph), vector<vector<int>>(size(graph), vector<int>(2)));
        queue<tuple<int, int, int>> q1;
        queue<tuple<int, int, int>> q2;
        for(int i = 0; i < size(graph); ++i) {
            if (i == HOLE) {
                continue;
            }
            color[HOLE][i][CAT - 1] = MOUSE;
            q1.emplace(HOLE, i, CAT);
            for (const auto& t : {MOUSE, CAT}) {
                color[i][i][t - 1] = CAT;
                q2.emplace(i, i, t);
            }
        }
        while (!empty(q1)) {
            const auto [i, j, t] = q1.front(); q1.pop();
            for (const auto& [ni, nj, nt] : parents(graph, i, j, t)) {
                if (color[ni][nj][nt - 1] != DRAW) {
                    continue;
                }
                if (t == CAT) {
                    color[ni][nj][nt - 1] = MOUSE;
                    q1.emplace(ni, nj, nt);
                    continue;
                }
                --degree[ni][nj][nt - 1];
                if (!degree[ni][nj][nt - 1]) {
                    color[ni][nj][nt - 1] = MOUSE;
                    q1.emplace(ni, nj, nt);
                }
            }
        }
        while (!empty(q2)) {
            const auto [i, j, t] = q2.front(); q2.pop();
            for (const auto& [ni, nj, nt] : parents(graph, i, j, t)) {
                if (color[ni][nj][nt - 1] != DRAW) {
                    continue;
                }
                if (t == MOUSE) {
                    color[ni][nj][nt - 1] = CAT;
                    q2.emplace(ni, nj, nt);
                    continue;
                }
                --degree[ni][nj][nt - 1];
                if (!degree[ni][nj][nt - 1]) {
                    color[ni][nj][nt - 1] = CAT;
                    q2.emplace(ni, nj, nt);
                }
            }
        }
        return color[MOUSE_START][CAT_START][MOUSE - 1];
    }

