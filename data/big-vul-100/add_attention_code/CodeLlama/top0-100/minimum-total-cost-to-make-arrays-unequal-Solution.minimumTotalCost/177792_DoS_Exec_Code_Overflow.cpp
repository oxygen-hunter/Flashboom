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


    long long minimumTotalCost(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> cnt;
        int64_t result = 0;
        for (int i = 0; i < size(nums1); ++i) {
            if (nums1[i] != nums2[i]) {
                continue;
            }
            ++cnt[nums1[i]];
            result += i;
        }
        if (empty(cnt)) {
            return 0;
        }
        const int majority = max_element(cbegin(cnt), cend(cnt),
                                         [](const auto& a, const auto& b) {
                                                return a.second < b.second;
                                         })->first;
        int remain = cnt[majority] - (accumulate(cbegin(cnt), cend(cnt), 0,
                                                 [](const auto& total, const auto& x) {
                                                     return total + x.second;
                                                 }) - cnt[majority]);
        if (remain <= 0) {
            return result;
        }
        for (int i = 0; i < size(nums1); ++i) {
            if (nums1[i] == nums2[i] || nums1[i] == majority || nums2[i] == majority) {
                continue;
            }
            result += i;
            if (--remain == 0) {
                return result;
            }
        }
        return -1;
    }


