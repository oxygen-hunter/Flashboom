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


    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        vector<pair<int, int>> idle;
        for (int i = 0; i < size(servers); ++i) {
            idle.emplace_back(servers[i], i);
        }
        make_heap(begin(idle), end(idle), greater<>());
        vector<tuple<int, int, int>> working;

        vector<int> result;
        for (int i = 0, t = 0; i < size(tasks); ++i) {
            t = !empty(idle) ? max(t, i) : get<0>(working.front());
            while (!empty(working) && get<0>(working.front()) <= t) {
                const auto [_, w, idx] = working.front(); pop_heap(begin(working), end(working), greater<>()); working.pop_back();
                idle.emplace_back(w, idx); push_heap(begin(idle), end(idle), greater<>());
            }
            const auto [w, idx] = idle.front(); pop_heap(begin(idle), end(idle), greater<>()); idle.pop_back();
            working.emplace_back(t + tasks[i], w, idx); push_heap(begin(working), end(working), greater<>());
            result.emplace_back(idx);
        }
        return result;
    }


