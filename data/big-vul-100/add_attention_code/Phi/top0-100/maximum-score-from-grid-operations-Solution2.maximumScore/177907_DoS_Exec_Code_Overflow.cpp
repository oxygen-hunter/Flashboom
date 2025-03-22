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

    long long maximumScore(vector<vector<int>>& grid) {
        vector<int64_t> prefix(size(grid)+ 1);
        for (int i = 0; i < size(grid); ++i) {
            prefix[i + 1] = prefix[i] + grid[i][0];
        }
        // dp[0][i]: the maximum score from 0 to the current column, and the current column has i black cells, without scoring the white cells of the current column
        // dp[1][i]: the maximum score from 0 to the current column, and the current column has i black cells, with scoring the white cells of the current column
        vector<vector<int64_t>> dp(2, vector<int64_t>(size(grid) + 1));
        for (int j = 1; j < size(grid[0]); ++j) {
            vector<int64_t> new_prefix(size(grid)+ 1);
            for (int i = 0; i < size(grid); ++i) {
                new_prefix[i + 1] = new_prefix[i] + grid[i][j];
            }
            vector<vector<int64_t>> new_dp(2, vector<int64_t>(size(grid) + 1));
            for (int i = 0; i <= size(grid); ++i) {
                for (int k = 0; k <= size(grid); ++k) {
                    new_dp[0][i] = max(new_dp[0][i], max(prefix[i] - prefix[k], static_cast<int64_t>(0)) + dp[0][k]);
                    new_dp[1][i] = max(new_dp[1][i], dp[1][k] + max(new_prefix[k] - new_prefix[i], static_cast<int64_t>(0)));
                }
                new_dp[0][i] = max(new_dp[0][i], ranges::max(dp[1]));
                new_dp[1][i] = max(new_dp[1][i], new_dp[0][i]);
            }
            dp = move(new_dp);
            prefix = move(new_prefix);
        }
        return ranges::max(dp[1]);
    }

