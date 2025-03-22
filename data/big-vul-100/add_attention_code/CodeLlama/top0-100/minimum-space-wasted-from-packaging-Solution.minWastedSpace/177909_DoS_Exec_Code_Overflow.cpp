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


    int minWastedSpace(vector<int>& packages, vector<vector<int>>& boxes) {
        static const int MOD = 1e9 + 7;
        static const int64_t INF = numeric_limits<int64_t>::max();

        sort(begin(packages), end(packages));
        int64_t result = INF;
        for (auto& box : boxes) {
            sort(begin(box), end(box));
            if (box.back() < packages.back()) {
                continue;
            }
            int64_t curr = 0;
            auto left = cbegin(packages);
            for (const auto& b : box) {
                auto right = upper_bound(left, cend(packages), b);
                curr += b * (right - left);
                left = right;
            }
            result = min(result, curr);
        }
        int64_t total = accumulate(cbegin(packages), cend(packages), 0LL);
        return result != INF ? (result - total) % MOD : -1;
    }


