void Splash::scaleMaskYdXu(SplashImageMaskSource src, void *srcData,
			   int srcWidth, int srcHeight,
			   int scaledWidth, int scaledHeight,
			   SplashBitmap *dest) {
  Guchar *lineBuf;
  Guint *pixBuf;
  Guint pix;
   Guchar *destPtr;
   int yp, yq, xp, xq, yt, y, yStep, xt, x, xStep, d;
   int i, j;
 
   yp = srcHeight / scaledHeight;
  lineBuf = (Guchar *)gmalloc(srcWidth);
  pixBuf = (Guint *)gmallocn(srcWidth, sizeof(int));

  yt = 0;

  destPtr = dest->data;
  for (y = 0; y < scaledHeight; ++y) {

   yt = 0;
 
  destPtr = dest->data;
   for (y = 0; y < scaledHeight; ++y) {
 
    }

    memset(pixBuf, 0, srcWidth * sizeof(int));
    for (i = 0; i < yStep; ++i) {
      (*src)(srcData, lineBuf);
      for (j = 0; j < srcWidth; ++j) {
	pixBuf[j] += lineBuf[j];
      }
    }

    xt = 0;
    d = (255 << 23) / yStep;

    for (x = 0; x < srcWidth; ++x) {

      if ((xt += xq) >= srcWidth) {
	xt -= srcWidth;
	xStep = xp + 1;
      } else {
	xStep = xp;
      }

      pix = pixBuf[x];
      pix = (pix * d) >> 23;

      for (i = 0; i < xStep; ++i) {
	*destPtr++ = (Guchar)pix;
      }
    }
  }

  gfree(pixBuf);
  gfree(lineBuf);
}


    int mergeStones(vector<int>& stones, int K) {
        if ((stones.size() - 1) % (K - 1)) {
            return -1;
        }
        vector<int> prefix(stones.size() + 1, 0);
        partial_sum(cbegin(stones), cend(stones), next(begin(prefix)), plus<int>());

        vector<vector<int> > dp(stones.size(), vector<int>(stones.size()));
        for (int l = K - 1; l < stones.size(); ++l) {
            for (int i = 0; i + l < stones.size(); ++i) {
                dp[i][i + l] = numeric_limits<int>::max();
                for (int j = i; j + 1 <= i + l; j += K - 1) {
                    dp[i][i + l] = min(dp[i][i + l], dp[i][j] + dp[j + 1][i + l]);
                }
                if (l % (K - 1) == 0) {
                    dp[i][i + l] += prefix[i + l + 1] - prefix[i];
                }
            }
        }
        return dp[0][stones.size() - 1];
    }


