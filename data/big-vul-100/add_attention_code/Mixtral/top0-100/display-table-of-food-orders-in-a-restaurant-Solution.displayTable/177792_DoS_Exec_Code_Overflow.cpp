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

    vector<vector<string>> displayTable(vector<vector<string>>& orders) {
        map<int, unordered_map<string, int>> table_count;
        set<string> foods;
        for (const auto& order : orders) {
            ++table_count[stoi(order[1])][order[2]];
            foods.emplace(order[2]);
        }
        vector<vector<string>> result = {{"Table"}};
        copy(foods.cbegin(), foods.cend(), back_inserter(result.back()));
        for (const auto& kvp: table_count) {
            result.push_back({to_string(kvp.first)});
            transform(foods.cbegin(), foods.cend(), back_inserter(result.back()),
                      [&kvp](const auto& food) {
                          return to_string(kvp.second.count(food) ? kvp.second.at(food) : 0);
                      });
        }
        return result;
    }

