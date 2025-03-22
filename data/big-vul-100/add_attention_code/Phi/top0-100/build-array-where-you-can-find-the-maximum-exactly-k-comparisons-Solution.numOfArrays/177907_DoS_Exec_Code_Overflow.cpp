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

