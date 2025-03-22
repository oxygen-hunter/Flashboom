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


    int superpalindromesInRange(string L, string R) {
        const auto K = static_cast<int>(pow(10, (R.length() + 1) * 0.25));
        const int64_t l = stol(L), r = stol(R);
        int result = 0;

        // count odd length
        for (int k = 0; k < K; ++k) {
            const string s = to_string(k), rev_s(s.rbegin(), s.rend());
            int64_t v = stol(s + rev_s.substr(1));
            v *= v;
            if (v > r) {
                break;
            }
            if (v >= l && is_palindrome(v)) {
                ++result;
            }
        }

        // count even length
        for (int k = 0; k < K; ++k) {
            const string s = to_string(k), rev_s(s.rbegin(), s.rend());
            int64_t v = stol(s + rev_s);
            v *= v;
            if (v > r) {
                break;
            }
            if (v >= l && is_palindrome(v)) {
                ++result;
            }
        }

        return result;
    }


