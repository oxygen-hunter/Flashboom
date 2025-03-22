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


        int jump(int A[], int n) {
            int ans = 0;
            int last = 0;
            int cur = 0;         // at most position by further jump
            for(int i = 0, next; i < n; ++i) {
                if(i > last) {   // he cannot reach "i" by current jumps
                    ++ans;       // so he should jump one more time
                    last = cur;  // to reach at most position
                }
                cur = max(cur, i + A[i]); // update at most position by further jump
            }
            return ans;
        }


