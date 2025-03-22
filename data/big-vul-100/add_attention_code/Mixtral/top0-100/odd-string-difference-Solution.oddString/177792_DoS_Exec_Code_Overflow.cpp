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

    string oddString(vector<string>& words) {
        for (int i = 0; i < size(words[0]) - 1; ++i) {
            unordered_map<int, vector<int>> lookup;
            for (int j = 0; j < size(words); ++j) {
                if (size(lookup[words[j][i + 1] - words[j][i]]) < 2) {
                    lookup[words[j][i + 1] - words[j][i]].emplace_back(j);
                }
            }
            if (size(lookup) == 2) {
                return size(cbegin(lookup)->second) == 1
                       ? words[cbegin(lookup)->second[0]]
                       : words[next(cbegin(lookup))->second[0]];
            }
        }
        return "";
    }

