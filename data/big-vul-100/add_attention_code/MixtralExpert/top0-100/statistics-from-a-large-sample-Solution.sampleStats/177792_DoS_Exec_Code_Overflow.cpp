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


    vector<double> sampleStats(vector<int>& count) {
        const double mi = distance(count.cbegin(), find_if(count.cbegin(), count.cend(), 
                                   [](int x) { return x != 0; }));
        
        const double ma = count.size() - 1 - 
                          distance(count.crbegin(), find_if(count.crbegin(), count.crend(), 
                                   [](int x) { return x != 0; }));
        
        const auto& n = accumulate(count.cbegin(), count.cend(), 0);
        double total = 0.0;
        for (int i = 0; i < count.size(); ++i) {
            total += double(i) * count[i];
        }
        const double mean = total / n;
        
        const double mode = distance(count.cbegin(), max_element(count.cbegin(), count.cend()));
        
        for (int i = 1; i < count.size(); ++i) {
            count[i] += count[i - 1];
        }
        const auto& median1 = distance(count.cbegin(), lower_bound(count.cbegin(), count.cend(), (n + 1) / 2));
        const auto& median2 = distance(count.cbegin(), lower_bound(count.cbegin(), count.cend(), (n + 2) / 2));
        const double median = (median1 + median2) / 2.0;
        
        return {mi, ma, mean, median, mode};
    }


