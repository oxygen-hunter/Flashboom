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

    int numOfArrays(int n, int m, int k) {
        static const int MOD = 1e9 + 7;
        // dp[l][i][j] = number of ways of constructing array length l with max element i at search cost j
        vector<vector<vector<uint64_t>>> dp(2, vector<vector<uint64_t>>(m + 1, vector<uint64_t>(k + 1)));
        // prefix_dp[l][i][j] = sum(dp[l][i][j] for i in [1..i])
        vector<vector<vector<uint64_t>>> prefix_dp(2, vector<vector<uint64_t>>(m + 1, vector<uint64_t>(k + 1)));
        for (uint64_t i = 1; i <= m; ++i) {
            dp[1][i][1] = 1;
            prefix_dp[1][i][1] = (prefix_dp[1][i - 1][1] + dp[1][i][1]) % MOD;
        }
        for (uint64_t l = 2; l <= n; ++l) {
            for (uint64_t i = 1; i <= m; ++i) {
                for (uint64_t j = 1; j <= k; ++j) {
                    dp[l % 2][i][j] = (i * dp[(l - 1) % 2][i][j] % MOD + prefix_dp[(l - 1) % 2][i - 1][j - 1]) % MOD;
                    prefix_dp[l % 2][i][j] = (prefix_dp[l % 2][i - 1][j] + dp[l % 2][i][j]) % MOD;
                }
            }
        }
        return prefix_dp[n % 2][m][k];
    }

