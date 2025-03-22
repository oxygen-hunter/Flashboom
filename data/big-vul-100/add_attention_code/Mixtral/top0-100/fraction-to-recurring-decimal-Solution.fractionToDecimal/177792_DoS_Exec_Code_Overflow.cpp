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

    string fractionToDecimal(int numerator, int denominator) {
        string result;
        if ((numerator ^ denominator) >> 31 && numerator != 0) {
            result = "-";
        }

        auto dvd = llabs(numerator);
        auto dvs = llabs(denominator);
        result += to_string(dvd / dvs);
        dvd %= dvs;
        if (dvd > 0) {
            result += ".";
        }
        
        unordered_map<long long, int> lookup;
        while (dvd && !lookup.count(dvd)) {
            lookup[dvd] = result.length();
            dvd *= 10;
            result += to_string(dvd / dvs);
            dvd %= dvs;
        }

        if (lookup.count(dvd)) {
            result.insert(lookup[dvd], "(");
            result.push_back(')');
        }
        return result;
    }

