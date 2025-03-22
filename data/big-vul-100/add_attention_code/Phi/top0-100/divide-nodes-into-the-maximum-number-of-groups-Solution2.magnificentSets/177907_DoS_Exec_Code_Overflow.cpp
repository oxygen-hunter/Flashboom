void Splash::scaleMaskYuXd(SplashImageMaskSource src, void *srcData,
			   int srcWidth, int srcHeight,
			   int scaledWidth, int scaledHeight,
			   SplashBitmap *dest) {
  Guchar *lineBuf;
  Guint pix;
   Guchar *destPtr0, *destPtr;
   int yp, yq, xp, xq, yt, y, yStep, xt, x, xStep, xx, d, d0, d1;
   int i;
 
   yp = scaledHeight / srcHeight;
  lineBuf = (Guchar *)gmalloc(srcWidth);

  yt = 0;

  destPtr0 = dest->data;
  for (y = 0; y < srcHeight; ++y) {

   yt = 0;
 
  destPtr0 = dest->data;
   for (y = 0; y < srcHeight; ++y) {
 
    }

    (*src)(srcData, lineBuf);

    xt = 0;
    d0 = (255 << 23) / xp;
    d1 = (255 << 23) / (xp + 1);

    xx = 0;
    for (x = 0; x < scaledWidth; ++x) {

      if ((xt += xq) >= scaledWidth) {
	xt -= scaledWidth;
	xStep = xp + 1;
	d = d1;
      } else {
	xStep = xp;
	d = d0;
      }

      pix = 0;
      for (i = 0; i < xStep; ++i) {
	pix += lineBuf[xx++];
      }
      pix = (pix * d) >> 23;

      for (i = 0; i < yStep; ++i) {
	destPtr = destPtr0 + i * scaledWidth + x;
	*destPtr = (Guchar)pix;
      }
    }

    destPtr0 += yStep * scaledWidth;
  }

  gfree(lineBuf);
}

    int magnificentSets(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            adj[e[0] - 1].emplace_back(e[1] - 1);
            adj[e[1] - 1].emplace_back(e[0] - 1);
        }
        vector<bool> lookup(n);
        const auto& bfs = [&](int u) {
            vector<int> group = {u};
            vector<int> q = {u};
            lookup[u] = true;
            while (!empty(q)) {
                vector<int> new_q;
                for (const auto& u : q) {
                    group.emplace_back(u);
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
            return group;
        };
        const auto& bfs2 = [&](int u) {
            int result = 0;
            vector<bool> lookup(n);
            unordered_set<int> q = {u};
            lookup[u] = true;
            for (; !empty(q); ++result) {
                unordered_set<int> new_q;
                for (const auto& u : q) {
                    for (const auto& v : adj[u]) {
                        if (q.count(v)) {
                            return 0;
                        }
                        if (lookup[v]) {
                            continue;
                        }
                        lookup[v] = true;
                        new_q.emplace(v);
                    }
                }
                q = move(new_q);
            }
            return result;
        };

        int result = 0;
        for (int u = 0; u < n; ++u) {
            if (lookup[u]) {
                continue;
            }
            const auto& group = bfs(u);
            int mx = 0;
            for (const auto& u : group) {
                const int d = bfs2(u);
                if (d == 0) {
                    return -1;
                }
                mx = max(mx, d);
            }
            result += mx;
        }
        return result;
    }

