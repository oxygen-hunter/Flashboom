void Splash::scaleMaskYdXu(SplashImageMaskSource src, void *srcData,
			   int srcWidth, int srcHeight,
			   int scaledWidth, int scaledHeight,
			   SplashBitmap *dest) {
  Guchar *lineBuf;
  Guint *pixBuf;
  Guint pix;
   Guchar *destPtr;
   int yp, yq, xp, xq, yt, y, yStep, xt, x, xStep, d;
   int i, j;
 
   yp = srcHeight / scaledHeight;
  lineBuf = (Guchar *)gmalloc(srcWidth);
  pixBuf = (Guint *)gmallocn(srcWidth, sizeof(int));

  yt = 0;

  destPtr = dest->data;
  for (y = 0; y < scaledHeight; ++y) {

   yt = 0;
 
  destPtr = dest->data;
   for (y = 0; y < scaledHeight; ++y) {
 
    }

    memset(pixBuf, 0, srcWidth * sizeof(int));
    for (i = 0; i < yStep; ++i) {
      (*src)(srcData, lineBuf);
      for (j = 0; j < srcWidth; ++j) {
	pixBuf[j] += lineBuf[j];
      }
    }

    xt = 0;
    d = (255 << 23) / yStep;

    for (x = 0; x < srcWidth; ++x) {

      if ((xt += xq) >= srcWidth) {
	xt -= srcWidth;
	xStep = xp + 1;
      } else {
	xStep = xp;
      }

      pix = pixBuf[x];
      pix = (pix * d) >> 23;

      for (i = 0; i < xStep; ++i) {
	*destPtr++ = (Guchar)pix;
      }
    }
  }

  gfree(pixBuf);
  gfree(lineBuf);
}


    vector<vector<int>> highestRankedKItems(vector<vector<int>>& grid, vector<int>& pricing, vector<int>& start, int k) {
        static const vector<pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        vector<pair<int, int>> q = {{start[0], start[1]}};
        vector<vector<int>> lookup(size(grid), vector<int>(size(grid[0]), -1));
        int d = lookup[start[0]][start[1]] = 0;
        auto compare = [&](const auto& x, const auto& y) {
            return make_tuple(lookup[x[0]][x[1]], grid[x[0]][x[1]], x[0], x[1]) <
                   make_tuple(lookup[y[0]][y[1]], grid[y[0]][y[1]], y[0], y[1]);
        };
        vector<vector<int>> result;
        while (!empty(q)) {
            if (size(result) >= k) {
                if (size(result) > k) {
                    nth_element(begin(result), begin(result) + k, end(result), compare);
                    result.resize(k);
                }
                break;
            }
            vector<pair<int, int>> new_q;
            for (const auto& [r, c] : q) {
                if (pricing[0] <= grid[r][c] && grid[r][c] <= pricing[1]) {
                    result.push_back({r, c});
                }
                for (const auto& [dr, dc] : directions) {
                    const int nr = r + dr, nc = c + dc;
                    if (!((0 <= nr && nr < size(grid)) && (0 <= nc && nc < size(grid[0])) &&
                           grid[nr][nc] && lookup[nr][nc] == -1)) {
                        continue;
                    }
                    lookup[nr][nc] = d + 1;
                    new_q.emplace_back(nr, nc);
                }
            }
            q = move(new_q);
            ++d;
        }
        sort(begin(result), end(result), compare);
        return result;
    }


