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


        bool searchMatrix(vector<vector<int> > &matrix, int target) {
            if(matrix.empty()) return false;

            const size_t m = matrix.size();
            const size_t n = matrix.front().size();

            int start = 0, end = m * n;

            while(start < end) {
                int mid = (start + end) / 2;
                int value = matrix[mid / n][mid % n];
                if(target == value)
                    return true;
                else if (value < target)
                    start = mid + 1;
                else
                    end = mid;
            }
            return false;
        }


