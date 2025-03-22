void Splash::arbitraryTransformMask(SplashImageMaskSource src, void *srcData,
				    int srcWidth, int srcHeight,
				    SplashCoord *mat, GBool glyphMode) {
  SplashBitmap *scaledMask;
  SplashClipResult clipRes, clipRes2;
  SplashPipe pipe;
  int scaledWidth, scaledHeight, t0, t1;
  SplashCoord r00, r01, r10, r11, det, ir00, ir01, ir10, ir11;
  SplashCoord vx[4], vy[4];
  int xMin, yMin, xMax, yMax;
  ImageSection section[3];
  int nSections;
  int y, xa, xb, x, i, xx, yy;

  vx[0] = mat[4];                    vy[0] = mat[5];
  vx[1] = mat[2] + mat[4];           vy[1] = mat[3] + mat[5];
  vx[2] = mat[0] + mat[2] + mat[4];  vy[2] = mat[1] + mat[3] + mat[5];
  vx[3] = mat[0] + mat[4];           vy[3] = mat[1] + mat[5];

  xMin = imgCoordMungeLowerC(vx[0], glyphMode);
  xMax = imgCoordMungeUpperC(vx[0], glyphMode);
  yMin = imgCoordMungeLowerC(vy[0], glyphMode);
  yMax = imgCoordMungeUpperC(vy[0], glyphMode);
  for (i = 1; i < 4; ++i) {
    t0 = imgCoordMungeLowerC(vx[i], glyphMode);
    if (t0 < xMin) {
      xMin = t0;
    }
    t0 = imgCoordMungeUpperC(vx[i], glyphMode);
    if (t0 > xMax) {
      xMax = t0;
    }
    t1 = imgCoordMungeLowerC(vy[i], glyphMode);
    if (t1 < yMin) {
      yMin = t1;
    }
    t1 = imgCoordMungeUpperC(vy[i], glyphMode);
    if (t1 > yMax) {
      yMax = t1;
    }
  }
  clipRes = state->clip->testRect(xMin, yMin, xMax - 1, yMax - 1);
  opClipRes = clipRes;
  if (clipRes == splashClipAllOutside) {
    return;
  }

  if (mat[0] >= 0) {
    t0 = imgCoordMungeUpperC(mat[0] + mat[4], glyphMode) -
         imgCoordMungeLowerC(mat[4], glyphMode);
  } else {
    t0 = imgCoordMungeUpperC(mat[4], glyphMode) -
         imgCoordMungeLowerC(mat[0] + mat[4], glyphMode);
  }
  if (mat[1] >= 0) {
    t1 = imgCoordMungeUpperC(mat[1] + mat[5], glyphMode) -
         imgCoordMungeLowerC(mat[5], glyphMode);
  } else {
    t1 = imgCoordMungeUpperC(mat[5], glyphMode) -
         imgCoordMungeLowerC(mat[1] + mat[5], glyphMode);
  }
  scaledWidth = t0 > t1 ? t0 : t1;
  if (mat[2] >= 0) {
    t0 = imgCoordMungeUpperC(mat[2] + mat[4], glyphMode) -
         imgCoordMungeLowerC(mat[4], glyphMode);
  } else {
    t0 = imgCoordMungeUpperC(mat[4], glyphMode) -
         imgCoordMungeLowerC(mat[2] + mat[4], glyphMode);
  }
  if (mat[3] >= 0) {
    t1 = imgCoordMungeUpperC(mat[3] + mat[5], glyphMode) -
         imgCoordMungeLowerC(mat[5], glyphMode);
  } else {
    t1 = imgCoordMungeUpperC(mat[5], glyphMode) -
         imgCoordMungeLowerC(mat[3] + mat[5], glyphMode);
  }
  scaledHeight = t0 > t1 ? t0 : t1;
  if (scaledWidth == 0) {
    scaledWidth = 1;
  }
  if (scaledHeight == 0) {
    scaledHeight = 1;
  }

  r00 = mat[0] / scaledWidth;
  r01 = mat[1] / scaledWidth;
  r10 = mat[2] / scaledHeight;
  r11 = mat[3] / scaledHeight;
  det = r00 * r11 - r01 * r10;
  if (splashAbs(det) < 1e-6) {
    return;
  }
  ir00 = r11 / det;
  ir01 = -r01 / det;
  ir10 = -r10 / det;
  ir11 = r00 / det;

   scaledMask = scaleMask(src, srcData, srcWidth, srcHeight,
 			 scaledWidth, scaledHeight);
 
   i = (vy[2] <= vy[3]) ? 2 : 3;
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

