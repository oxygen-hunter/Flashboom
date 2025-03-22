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


    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        static const int K = 3;

        vector<vector<int>> left{grid}, right{grid};
        for (int i = 1; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]) - 1; ++j) {
                left[i][j] += left[i - 1][j + 1];
            }
        }
        for (int i = 1; i < size(grid); ++i) {
            for (int j = 1; j < size(grid[0]); ++j) {
                right[i][j] += right[i - 1][j - 1];
            }
        }
        priority_queue<int, vector<int>, greater<int>> min_heap;
        unordered_set<int> lookup;
        for (int k = 0; k <= (min(size(grid), size(grid[0])) + 1) / 2; ++k) {
            for (int i = k; i < size(grid) - k; ++i) {
                for (int j = k; j < size(grid[0]) - k; ++j) {
                    int total = k ? ((left[i][j - k] - left[i - k][j]) + (right[i][j + k] - right[i - k][j]) + grid[i - k][j]) +  
                                    ((left[i + k][j] - left[i][j + k]) + (right[i + k][j] - right[i][j - k]) - grid[i + k][j])
                                  : grid[i][j];
                    if (lookup.count(total)) {
                        continue;
                    }
                    lookup.emplace(total);
                    min_heap.emplace(total);
                    if (size(min_heap) == K + 1) {
                        lookup.erase(min_heap.top()); min_heap.pop();
                    }
                }
            }
        }
        vector<int> result;
        while (!empty(min_heap)) {
            result.emplace_back(min_heap.top()); min_heap.pop();
        }
        reverse(begin(result), end(result));
        return result;
    }


