SplashBitmap::SplashBitmap(int widthA, int heightA, int rowPad,
			   SplashColorMode modeA, GBool alphaA,
			   GBool topDown) {
  width = widthA;
  height = heightA;
  mode = modeA;
  switch (mode) {
  case splashModeMono1:
    rowSize = (width + 7) >> 3;
    break;
  case splashModeMono8:
    rowSize = width;
    break;
  case splashModeRGB8:
  case splashModeBGR8:
    rowSize = width * 3;
    break;
  case splashModeXBGR8:
    rowSize = width * 4;
    break;
#if SPLASH_CMYK
  case splashModeCMYK8:
    rowSize = width * 4;
    break;
#endif
   }
   rowSize += rowPad - 1;
   rowSize -= rowSize % rowPad;
  data = (SplashColorPtr)gmalloc(rowSize * height);
   if (!topDown) {
     data += (height - 1) * rowSize;
     rowSize = -rowSize;
   }
   if (alphaA) {
    alpha = (Guchar *)gmalloc(width * height);
   } else {
     alpha = NULL;
   }
}

    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        const auto& ceil_divide = [](const auto& a, const auto& b) {
            return (a + b - 1) / 2;
        };

        const auto& tree_diameter = [](const auto& edges) {
            vector<vector<int>> adj(size(edges) + 1);
            for (const auto& e : edges) {
                adj[e[0]].emplace_back(e[1]);
                adj[e[1]].emplace_back(e[0]);
            }
            int result = 0;
            const auto& bfs = [&](int root) {
                int d = -1, new_root = -1;
                vector<bool> lookup(size(adj));
                lookup[root] = true;
                vector<int> q = {root};
                while (!empty(q)) {
                    ++d;
                    new_root = q[0];
                    vector<int> new_q;
                    for (const auto& u : q) {
                        for (const auto& v : adj[u]) {
                            if (lookup[v]) {
                                continue;
                            }
                            lookup[v] = true;
                            new_q.emplace_back(v);
                        }
                    }
                    q = move(new_q);
                }
                return pair(d, new_root);
            };

            const auto& [_, root] = bfs(0);
            const auto& [d, __] = bfs(root);
            return d;
        };

        const int d1 = tree_diameter(edges1);
        const int d2 = tree_diameter(edges2);
        return max({ceil_divide(d1, 2) + 1 + ceil_divide(d2, 2), d1, d2});
    }

