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

    int dieSimulator(int n, vector<int>& rollMax) {
        static const int MOD = 1e9 + 7;
        vector<vector<int>> dp;
        for (int i = 0; i < 6; ++i) {
            dp.emplace_back(rollMax[i]);
            dp[i][0] = 1;  // 0-indexed
        }
        while (--n) {
            vector<vector<int>> new_dp;
            for (int i = 0; i < 6; ++i) {
                new_dp.emplace_back(rollMax[i]);  
            }
            for (int i = 0; i < 6; ++i) {
                for (int k = 0; k < rollMax[i]; ++k) {
                    for (int j = 0; j < 6; ++j) {
                        if (i == j) {
                            if (k < rollMax[i] - 1) {  // 0-indexed
                                new_dp[j][k + 1] = (new_dp[j][k + 1] + dp[i][k]) % MOD;
                            }
                        } else {
                            new_dp[j][0] = (new_dp[j][0] + dp[i][k]) % MOD;
                        }
                    }
                }
            }
            dp = move(new_dp);
        }
        uint64_t result = 0;
        for (const auto& row : dp) {
            const auto& total =
                accumulate(row.cbegin(), row.cend(),
                           0ull,
                           [&](const auto& a, const auto& b) {
                               return (a + b) % MOD;
                           });
            result = (result + total) % MOD;
        }
        return result;
    }

