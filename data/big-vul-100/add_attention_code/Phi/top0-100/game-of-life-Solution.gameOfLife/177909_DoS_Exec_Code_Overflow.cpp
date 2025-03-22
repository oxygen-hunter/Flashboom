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

    void gameOfLife(vector<vector<int>>& board) {
        const int m = board.size(), n = m ? board[0].size() : 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int count = 0;
                // Count live cells in 3x3 block.
                for (int I = max(i - 1, 0); I < min(i + 2, m); ++I) {
                    for (int J = max(j - 1, 0); J < min(j + 2, n); ++J) {
                        count += board[I][J] & 1;
                    }
                }
                // if (count == 4 && board[i][j]) means:
                //     Any live cell with three live neighbors lives.
                // if (count == 3) means:
                //     Any live cell with two live neighbors.
                //     Any dead cell with exactly three live neighbors lives.
                if ((count == 4 && board[i][j]) || count == 3) {
                    board[i][j] |= 2;  // Mark as live. 
                }
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] >>= 1;  // Update to the next state.
            }
        }
    }

