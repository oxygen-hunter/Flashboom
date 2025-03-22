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


    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, TreeNode *> nodes;
        unordered_set<int> children;
        for (const auto& d : descriptions) {
            if (!nodes.count(d[0])) {
                nodes[d[0]] = new TreeNode(d[0]);
            }
            if (!nodes.count(d[1])) {
                nodes[d[1]] = new TreeNode(d[1]);
            }
            if (d[2]) {
                nodes[d[0]]->left = nodes[d[1]];
            } else {
                nodes[d[0]]->right = nodes[d[1]];
            }
            children.emplace(d[1]);
        }
        for (const auto& [k, v] : nodes) {
            if (!children.count(k)) {
                return v;
            }
        }
        return nullptr;
    }


