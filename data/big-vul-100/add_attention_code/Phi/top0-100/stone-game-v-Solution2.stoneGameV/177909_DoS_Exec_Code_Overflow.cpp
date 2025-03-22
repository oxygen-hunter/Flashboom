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

    int stoneGameV(vector<int>& stoneValue) {
        const int n = stoneValue.size();
        vector<int> prefix(n + 1);
        partial_sum(cbegin(stoneValue), cend(stoneValue), begin(prefix) + 1);

        vector<vector<int>> mid(n, vector<int>(n));
        for (int l = 1; l <= n; ++l) {
            for (int i = 0; i <= n - l; ++i) {
                const int j = i + l - 1;
                int p = (l == 1) ? i : mid[i][j - 1];
                while (prefix[p] - prefix[i] < prefix[j + 1] - prefix[p]) {
                    ++p;  // Time: O(n^2) in total
                }
                mid[i][j] = p;
            }
        }
        
        vector<vector<int>> rmq(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            rmq[i][i] = stoneValue[i];
        }

        vector<vector<int>> dp(n, vector<int>(n));
        for (int l = 2; l <= n; ++l) {
            for (int i = 0; i <= n - l; ++i) {
                const int j = i + l - 1;
                const int p = mid[i][j];
                int max_score = 0;
                if (prefix[p] - prefix[i] == prefix[j + 1] - prefix[p]) {
                    max_score = max(rmq[i][p - 1], rmq[j][p]);
                } else {
                    if (i <= p - 2) {
                        max_score = max(max_score, rmq[i][p - 2]);
                    }
                    if (p <= j) {
                        max_score = max(max_score, rmq[j][p]);
                    }
                }
                dp[i][j] = max_score;
                rmq[i][j] = max(rmq[i][j - 1], (prefix[j + 1] - prefix[i]) + max_score);
                rmq[j][i] = max(rmq[j][i + 1], (prefix[j + 1] - prefix[i]) + max_score);
            }
        }
        return dp[0][n - 1];
    }

