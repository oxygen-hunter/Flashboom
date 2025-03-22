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

    int deleteString(string s) {
        static const int MOD = 1e9 + 7;
        static vector<int> P = {113, 109};
        if (all_of(cbegin(s), cend(s), [&](const auto& x) { return x == s[0]; })) {
            return size(s);
        }
        vector<vector<int64_t>> power(size(P), vector<int64_t>(1, 1));
        vector<vector<int64_t>> prefix(size(P), vector<int64_t>(1));
        const auto& hash = [&](int i, int j) {
            vector<int> h(size(P));
            for (int idx = 0; idx < size(P); ++idx) {
                h[idx] = ((prefix[idx][j + 1] - prefix[idx][i] * power[idx][j - i + 1]) % MOD + MOD) % MOD;
            }
            return h;
        };
        for (const auto& x : s) {
            for (int idx = 0; idx < size(P); ++idx) {
                power[idx].emplace_back(power[idx].back() * P[idx] % MOD);
                prefix[idx].emplace_back((prefix[idx].back() * P[idx] + (x - 'a')) % MOD);
            }
        }
        vector<int> dp(size(s), 1);  // dp[i]: max operation count of s[i:]
        for (int i = size(s) - 2; i >= 0; --i) {              
            for (int j = 1; j <= (size(s) - i) / 2 ; ++j) {
                if (hash(i, i + j - 1) == hash(i + j, i + 2 * j - 1)) {
                    dp[i] = max(dp[i], dp[i + j] + 1);
                }
            }
        }
        return dp[0];
    }

