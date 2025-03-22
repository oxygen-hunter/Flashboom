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


        int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
            const int m = obstacleGrid.size();
            const int n = obstacleGrid[0].size();
            vector<int> v(n, 0);

            v[0] = 1;
            for(int i = 0; i < m; ++i) {
                if(obstacleGrid[i][0] != 0)
                    v[0] = 0;
                for(int j = 1; j < n; ++j) {
                    if(obstacleGrid[i][j] == 0)
                        v[j] += v[j - 1];
                    else
                        v[j] = 0;
                }
            }

            return v[n - 1];
        }


