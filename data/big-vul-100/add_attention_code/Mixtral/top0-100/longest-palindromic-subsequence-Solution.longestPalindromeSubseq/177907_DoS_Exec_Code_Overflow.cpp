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

    int longestPalindromeSubseq(string s) {
        if (s == string(s.rbegin(), s.rend())) {  // optional, to optimize special case
            return s.length();
        }
        
        vector<vector<int>> dp(2, vector<int>(s.size(), 1));
        for (int i = s.length() - 2; i >= 0; --i) {
            for (int j = i + 1; j < s.length(); ++j) {
                if (s[i] == s[j]) {
                    dp[i % 2][j] = (i + 1 <= j - 1) ? 2 + dp[(i + 1) % 2][j - 1] : 2;
                } else {
                    dp[i % 2][j] = max(dp[(i + 1) % 2][j], dp[i % 2][j - 1]);
                }
            }
        }
        return dp[0][s.length() - 1];
    }

