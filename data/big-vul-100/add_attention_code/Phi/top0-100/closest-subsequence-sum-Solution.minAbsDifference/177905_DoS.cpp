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

    int minAbsDifference(vector<int>& nums, int goal) {
        int mx = 0, mn = 0;
        for (const auto& x : nums) {
            if (x > 0) {
                mx += x;
            } else if (x < 0) {
                mn += x;
            }
        }
        if (goal > mx) {
            return goal - mx;
        }
        if (goal < mn) {
            return mn - goal;
        }
        int result = abs(goal);
        unordered_set<int> sums1{0};
        for (auto i = 0; i < size(nums) / 2; ++i) {
            for (const auto& x : vector<int>(cbegin(sums1), cend(sums1))) {
                if (!sums1.emplace(x + nums[i]).second) {
                    continue;
                }
                result = min(result, abs(goal - x - nums[i]));  // case of right half part is 0
            }
        }
        vector<int> sorted_sums1(cbegin(sums1), cend(sums1));  // Space: O(2^(n/2))
        sort(begin(sorted_sums1), end(sorted_sums1));  // Time: O((n/2) * 2^(n/2)) = O(n * 2^(n/2))
        unordered_set<int> sums2{0};
        for (int i = size(nums) / 2; i < size(nums); ++i) {
            for (const auto& x : vector<int>(cbegin(sums2), cend(sums2))) {
                if (!sums2.emplace(x + nums[i]).second) {
                    continue;
                }
                auto cit = lower_bound(cbegin(sorted_sums1), cend(sorted_sums1), goal - x - nums[i]);  // Time: O(2^(n/2)) * O(n/2)
                if (cit != cend(sorted_sums1)) {
                    result = min(result, abs(goal - x - nums[i] - *cit));
                }
                if (cit != cbegin(sorted_sums1)) {
                    result = min(result, abs(goal - x - nums[i] - *prev(cit)));
                }
                if (result == 0) {
                    return result;
                }
            }
        }
        return result;
    }

