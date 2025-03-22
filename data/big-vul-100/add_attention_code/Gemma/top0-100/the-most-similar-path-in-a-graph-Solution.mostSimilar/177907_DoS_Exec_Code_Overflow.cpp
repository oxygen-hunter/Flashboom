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


    vector<int> mostSimilar(int n, vector<vector<int>>& roads, vector<string>& names, vector<string>& targetPath) {
        vector<vector<int>> adj(n);
        for (const auto& road : roads) {
            adj[road[0]].emplace_back(road[1]);
            adj[road[1]].emplace_back(road[0]);
        }

        vector<vector<int>> dp(targetPath.size() + 1, vector<int>(n));
        for (int i = 1; i <= targetPath.size(); ++i) {
            for (int v = 0; v < n; ++v) {
                dp[i][v] = targetPath.size();
                for (const auto& u : adj[v]) {
                    dp[i][v] = min(dp[i][v], dp[i - 1][u]);
                }
                dp[i][v] += int(names[v] != targetPath[i - 1]);
            }
        }

        vector<int> path = {static_cast<int>(distance(cbegin(dp.back()), 
                                                      min_element(cbegin(dp.back()), cend(dp.back()))))};
        for (int i = targetPath.size(); i >= 2; --i) {
            for (const auto& u : adj[path.back()]) {
                if (dp[i - 1][u] + int(names[path.back()] != targetPath[i - 1]) == dp[i][path.back()]) {
                    path.emplace_back(u);
                    break;
                }
            }
        }
        reverse(begin(path), end(path));
        return path;
    }


