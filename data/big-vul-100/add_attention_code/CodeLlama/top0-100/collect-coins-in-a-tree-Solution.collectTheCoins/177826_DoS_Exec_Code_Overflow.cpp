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


    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        static const int DISTANCE = 2;

        vector<unordered_set<int>> adj(size(coins));
        for (const auto& e : edges) {
            adj[e[0]].emplace(e[1]);
            adj[e[1]].emplace(e[0]);
        }
        int n = size(coins);
        for (int i = 0; i < size(coins); ++i) {
            int u = i;
            while (size(adj[u]) == 1 && !coins[u]) {
                const int v = *cbegin(adj[u]);
                adj[u].erase(v);
                adj[v].erase(u);
                --n;
                u = v;
            }
        }
        vector<int> q;
        for (int u = 0; u < size(coins); ++u) {
            if (size(adj[u]) == 1) {
                q.emplace_back(u);
            }
        }
        for (int _ = 0; _ < DISTANCE; ++_) {
            vector<int> new_q;
            for (const auto& u : q) {
                if (empty(adj[u])) {
                    assert(n == 1);
                    break;
                }
                const int v = *cbegin(adj[u]);
                adj[u].erase(v);
                adj[v].erase(u);
                --n;
                if (size(adj[v]) == 1) {
                    new_q.emplace_back(v);
                }
            }
            q = move(new_q);
        }
        return (n - 1) * 2;
    }


