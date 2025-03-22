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

    bool hasValidPath(vector<vector<int>>& grid) {
        static const pair<int, int> E = {0,  1}, S = {1,  0},
                                    W = {0, -1}, N = {-1, 0};
        static const vector<vector<pair<int, int>>> directions = {
            {W, E}, {N, S},
            {W, S}, {S, E},
            {W, N}, {N, E}
        };

        for (auto [r, c] : directions.at(grid[0][0] - 1)) {
            if (!(0 <= r && r < grid.size() &&
                  0 <= c && c < grid[0].size())) {
                continue;
            }
            int pr = 0, pc = 0;
            while (r != grid.size() - 1 || c != grid[0].size() - 1) {
                bool is_found = false;
                for (const auto& [dx, dy] : directions.at(grid[r][c] - 1)) {
                    const auto& [nr, nc] = pair(r + dx, c + dy);
                    if ((nr == pr && nc == pc) ||
                        !(0 <= nr && nr < grid.size() &&
                          0 <= nc && nc < grid[0].size())) {
                        continue;
                    }
                    const auto& dirs = directions.at(grid[nr][nc] - 1);
                    if (find(cbegin(dirs), cend(dirs), pair(-dx, -dy)) == cend(dirs)) {
                        continue;
                    }
                    tie(pr, pc, r, c) = tuple(r, c, nr, nc);
                    is_found = true;
                    break;
                }
                if (!is_found) {
                    return false;
                }
            }
            return true;
        }
        return grid.size() == 1 && grid[0].size() == 1;
    }

