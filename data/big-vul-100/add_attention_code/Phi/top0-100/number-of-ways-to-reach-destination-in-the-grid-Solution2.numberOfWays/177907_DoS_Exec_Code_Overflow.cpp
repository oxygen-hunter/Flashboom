void Splash::scaleMaskYuXd(SplashImageMaskSource src, void *srcData,
			   int srcWidth, int srcHeight,
			   int scaledWidth, int scaledHeight,
			   SplashBitmap *dest) {
  Guchar *lineBuf;
  Guint pix;
   Guchar *destPtr0, *destPtr;
   int yp, yq, xp, xq, yt, y, yStep, xt, x, xStep, xx, d, d0, d1;
   int i;
 
   yp = scaledHeight / srcHeight;
  lineBuf = (Guchar *)gmalloc(srcWidth);

  yt = 0;

  destPtr0 = dest->data;
  for (y = 0; y < srcHeight; ++y) {

   yt = 0;
 
  destPtr0 = dest->data;
   for (y = 0; y < srcHeight; ++y) {
 
    }

    (*src)(srcData, lineBuf);

    xt = 0;
    d0 = (255 << 23) / xp;
    d1 = (255 << 23) / (xp + 1);

    xx = 0;
    for (x = 0; x < scaledWidth; ++x) {

      if ((xt += xq) >= scaledWidth) {
	xt -= scaledWidth;
	xStep = xp + 1;
	d = d1;
      } else {
	xStep = xp;
	d = d0;
      }

      pix = 0;
      for (i = 0; i < xStep; ++i) {
	pix += lineBuf[xx++];
      }
      pix = (pix * d) >> 23;

      for (i = 0; i < yStep; ++i) {
	destPtr = destPtr0 + i * scaledWidth + x;
	*destPtr = (Guchar)pix;
      }
    }

    destPtr0 += yStep * scaledWidth;
  }

  gfree(lineBuf);
}

    int numberOfWays(int n, int m, int k, vector<int>& source, vector<int>& dest) {
        static const int MOD = 1e9 + 7;
    
        int both_same = 0, row_same = 0, col_same = 0, no_same = 0;
        if (source == dest) {
            both_same = 1;
        } else if (source[0] == dest[0]) {
            row_same = 1;
        } else if (source[1] == dest[1]) {
            col_same = 1;
        } else {
            no_same = 1;
        }
        for (int _ = 0; _ < k; ++_) {
            tie(both_same, row_same, col_same, no_same) = tuple(
                (row_same + col_same) % MOD,
                (both_same * static_cast<int64_t>(m - 1) + row_same * static_cast<int64_t>(m - 2) + no_same) % MOD,
                (both_same * static_cast<int64_t>(n - 1) + col_same * static_cast<int64_t>(n - 2) + no_same) % MOD,
                (row_same * static_cast<int64_t>(n - 1) + col_same * static_cast<int64_t>(m - 1) + no_same * static_cast<int64_t>((n - 2) + (m - 2))) % MOD
            );
        }
        return both_same;
    }

