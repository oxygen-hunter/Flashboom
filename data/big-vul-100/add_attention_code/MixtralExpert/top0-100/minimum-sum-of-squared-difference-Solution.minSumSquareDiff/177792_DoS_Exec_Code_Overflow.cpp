SplashBitmap::SplashBitmap(int widthA, int heightA, int rowPad,
			   SplashColorMode modeA, GBool alphaA,
			   GBool topDown) {
  width = widthA;
  height = heightA;
  mode = modeA;
  switch (mode) {
  case splashModeMono1:
    rowSize = (width + 7) >> 3;
    break;
  case splashModeMono8:
    rowSize = width;
    break;
  case splashModeRGB8:
  case splashModeBGR8:
    rowSize = width * 3;
    break;
  case splashModeXBGR8:
    rowSize = width * 4;
    break;
#if SPLASH_CMYK
  case splashModeCMYK8:
    rowSize = width * 4;
    break;
#endif
   }
   rowSize += rowPad - 1;
   rowSize -= rowSize % rowPad;
  data = (SplashColorPtr)gmalloc(rowSize * height);
   if (!topDown) {
     data += (height - 1) * rowSize;
     rowSize = -rowSize;
   }
   if (alphaA) {
    alpha = (Guchar *)gmalloc(width * height);
   } else {
     alpha = NULL;
   }
}


    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        vector<int64_t> diffs(size(nums1));
        for (int i = 0; i < size(diffs); ++i) {
            diffs[i] = abs(nums1[i] - nums2[i]);
        }
        sort(rbegin(diffs), rend(diffs));
        int64_t k = min(static_cast<int64_t>(k1) + k2, accumulate(cbegin(diffs), cend(diffs), static_cast<int64_t>(0)));
        const auto& check = [&](int x) {
            return accumulate(cbegin(diffs), cend(diffs), 0ll,
                              [&](const auto& total, const auto& d) {
                                  return total + max(d - x, static_cast<int64_t>(0));
                              }) <= k;
        };
        int64_t left = 0, right = diffs[0];
        while (left <= right) {
            const int mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        k -= accumulate(cbegin(diffs), cend(diffs), 0ll,
                        [&](const auto& total, const auto& d) {
                            return total + max(d - left, static_cast<int64_t>(0));
                        });
        for (int i = 0; i < size(diffs); ++i) {
            diffs[i] = min(diffs[i], left) - int(i < k);
        }
        return accumulate(cbegin(diffs), cend(diffs), 0ll,
                          [](const auto& total, const auto& d) {
                              return total + d * d;
                          });
    }


