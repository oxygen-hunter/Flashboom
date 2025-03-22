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


    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        int max_f = *max_element(cbegin(forbidden), cend(forbidden));
        int max_val = (a >= b) ? x + b : max(x, max_f) + a + b;  // a may be a non-periodic area, (a+b) is a periodic area which is divided by gcd(a, b) and all points are reachable
        vector<unordered_set<int>> lookup(2); 
        for (const auto& pos : forbidden) {
            lookup[0].emplace(pos);
            lookup[1].emplace(pos);
        }
        int result = 0;
        vector<pair<int, int>> q = {{0, true}};
        lookup[0].emplace(0);
        while (!empty(q)) {
            vector<pair<int, int>> new_q;
            for (const auto& [pos, can_back] : q) {
                if (pos == x) {
                    return result;
                }
                if (pos + a <= max_val && !lookup[0].count(pos + a)) {
                    lookup[0].emplace(pos + a);
                    new_q.emplace_back(pos + a, true);
                }
                if (!can_back) {
                    continue;
                }
                if (pos - b >= 0 && !lookup[1].count(pos - b)) {
                    lookup[1].emplace(pos - b);
                    new_q.emplace_back(pos - b, false);
                }
            }
            q = move(new_q);
            ++result;
        }
        return -1;
    }


