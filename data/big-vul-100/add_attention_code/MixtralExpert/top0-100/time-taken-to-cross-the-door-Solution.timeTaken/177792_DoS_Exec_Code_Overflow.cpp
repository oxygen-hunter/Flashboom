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


    vector<int> timeTaken(vector<int>& arrival, vector<int>& state) {
        enum {UNKNOWN = -1, ENTERING, EXITING};
        vector<int> result(size(arrival));
        int curr = numeric_limits<int>::min(), direction = UNKNOWN;
        vector<queue<int>> q(2);
        const auto& go_until = [&](int t) {
            while (curr <= t && any_of(cbegin(q), cend(q), [](const auto& x) { return !empty(x); })) {
                if (empty(q[direction])) {
                    direction ^= 1;
                }
                result[q[direction].front()] = curr++;
                q[direction].pop();
            }
        };

        for (int i = 0; i < size(arrival); ++i) {
            go_until(arrival[i] - 1);
            q[state[i]].emplace(i);
            if (!(arrival[i] <= curr)) {
                curr = arrival[i], direction = EXITING;
            }
        }
        go_until(numeric_limits<int>::max());
        return result;
    }


