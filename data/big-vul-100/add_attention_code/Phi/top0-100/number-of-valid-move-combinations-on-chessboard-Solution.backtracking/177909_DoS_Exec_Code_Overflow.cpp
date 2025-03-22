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

    int backtracking(const vector<string>& pieces, const vector<vector<int>>& positions, int i, vector<vector<int>> *lookup) {
        static const unordered_map<string, vector<pair<int, int>>> directions = {
            {"rook", {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}},
            {"bishop", {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}},
            {"queen", {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}}
        };
        static const int all_mask = (1 << 7) - 1;  // at most 7 seconds in 8x8 board

        if (i == size(pieces)) {
            return 1;
        }
        int result = 0;
        int r = positions[i][0] - 1, c = positions[i][1] - 1;
        int mask = all_mask;
        if (!((*lookup)[r][c] & mask)) {
            (*lookup)[r][c] += mask;  // stopped at (r, c)
            result += backtracking(pieces, positions, i + 1, lookup);
            (*lookup)[r][c] -= mask;
        }
        for (const auto& [dr, dc] : directions.at(pieces[i])) {
            int bit = 1, nr = r + dr, nc = c + dc;
            int mask = all_mask;  // (mask&bit == 1): (log2(bit)+1)th second is occupied
            for (; 0 <= nr && nr < 8 && 0 <= nc && nc < 8 && !((*lookup)[nr][nc] & bit); bit <<= 1, nr += dr, nc += dc) {
                (*lookup)[nr][nc] += bit;
                mask -= bit;
                if (!((*lookup)[nr][nc] & mask)) {  // stopped at (nr, nc)
                    (*lookup)[nr][nc] += mask;
                    result += backtracking(pieces, positions, i + 1, lookup);
                    (*lookup)[nr][nc] -= mask;
                }
            }
            while (bit >> 1) {
                bit >>= 1, nr -= dr, nc -= dc;
                (*lookup)[nr][nc] -= bit;
            }
        }
        return result;
    }

