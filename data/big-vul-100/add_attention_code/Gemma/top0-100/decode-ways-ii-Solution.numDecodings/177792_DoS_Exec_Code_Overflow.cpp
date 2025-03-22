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


    int numDecodings(string s) {
        static const int M = 1000000007;
        static const int W = 3;
        vector<long long> dp(W);
        dp[0] = 1;
        dp[1] = s[0] == '*' ? 9 : (s[0] != '0' ? dp[0] : 0);
        for (int i = 1; i < s.length(); ++i) {
            if (s[i] == '*') {
                dp[(i + 1) % W] = 9 * dp[i % W];
                if (s[i - 1] == '1') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + 9 * dp[(i - 1) % W]) % M;
                } else if (s[i - 1] == '2') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + 6 * dp[(i - 1) % W]) % M;
                } else if (s[i - 1] == '*') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + 15 * dp[(i - 1) % W]) % M;
                }
            } else {
                dp[(i + 1) % W] = s[i] != '0' ? dp[i % W] : 0;
                if (s[i - 1] == '1') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + dp[(i - 1) % W]) % M;
                } else if (s[i - 1] == '2' && s[i] <= '6') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + dp[(i - 1) % W]) % M;
                } else if (s[i - 1] == '*') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + (s[i] <= '6' ? 2 : 1) * dp[(i - 1) % W]) % M;
                }
            }
        }
        return static_cast<int>(dp[s.length() % W]);
    }


