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

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        const auto& binary_search = [](int left, int right, const auto& check) {
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (check(mid)) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return left;
        };

        const auto& findKthInSortedArrays = [&](const auto& arrays, int k) {
            const auto& check = [&](int num) {
                int res = 0;
                for (const auto& arr : arrays) {
                    if (!empty(*arr)) {  // count the number of values which are less or equal to num
                        res += distance(cbegin(*arr), upper_bound(cbegin(*arr), cend(*arr), num));
                    }
                }
                return res >= k;
            };

            int left = numeric_limits<int>::max();
            int right = numeric_limits<int>::min();
            for (const auto arr : arrays) {
                if (!empty(*arr)) {
                    left = min(left, arr->front());
                    right = max(right, arr->back());
                }
            }
            return binary_search(left, right, check);
        };

        vector<vector<int> *> arrays{&nums1, &nums2};
        int total = accumulate(cbegin(arrays), cend(arrays), 0, [](const auto& x, const auto& y) {
            return x + size(*y);
        });
        if (total % 2 == 1) {
            return findKthInSortedArrays(arrays, total / 2 + 1);
        } else {
            return (findKthInSortedArrays(arrays, total / 2) +
                    findKthInSortedArrays(arrays, total / 2 + 1)) / 2.0;
        }
    }

