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


    int shortestSubarray(vector<int>& A, int K) {
        vector<int> accumulated_sum(A.size() + 1, 0);
        partial_sum(A.cbegin(), A.cend(), next(accumulated_sum.begin()), plus<int>());
        
        int result = numeric_limits<int>::max();
        deque<int> mono_increasing_q;
        for (int i = 0; i < accumulated_sum.size(); ++i) {
            while (!mono_increasing_q.empty() &&
                   accumulated_sum[i] <= accumulated_sum[mono_increasing_q.back()]) {
                mono_increasing_q.pop_back();
            }
            while (!mono_increasing_q.empty() &&
                   accumulated_sum[i] - accumulated_sum[mono_increasing_q.front()] >= K) {
                result = min(result, i - mono_increasing_q.front());
                mono_increasing_q.pop_front();
            }
            mono_increasing_q.emplace_back(i);
        }
        return result != numeric_limits<int>::max() ? result : -1;
    }


