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


    string bestHand(vector<int>& ranks, vector<char>& suits) {
        static const vector<string> LOOKUP = {"", "High Card", "Pair", "Three of a Kind", "Three of a Kind", "Three of a Kind"};
        if (all_of(cbegin(suits), cend(suits), [&](const auto& x) { return x == suits[0]; })) {
            return "Flush";
        }
        vector<int> cnt(13);
        for (const auto& x : ranks) {
            ++cnt[x - 1];
        }
        return LOOKUP[*max_element(cbegin(cnt), cend(cnt))];
    }


