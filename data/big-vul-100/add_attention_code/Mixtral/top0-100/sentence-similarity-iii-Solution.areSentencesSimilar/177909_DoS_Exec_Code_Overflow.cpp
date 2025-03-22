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

    bool areSentencesSimilar(string sentence1, string sentence2) {
        if (size(sentence1) > size(sentence2)) {
            swap(sentence1, sentence2);
        }
        int count = 0;
        for (int step = 0; step < 2; ++step) {
            for (int i = 0; i <= size(sentence1); ++i) {
                char c1 = i != size(sentence1) ? sentence1[step == 0 ? i : size(sentence1) - 1 - i] : ' ';
                char c2 = i != size(sentence2) ? sentence2[step == 0 ? i : size(sentence2) - 1 - i] : ' ';
                if (c1 != c2) {
                    break;
                }
                if (c1 == ' ') {
                    ++count;
                }
            }
        }
        return count >= count_if(cbegin(sentence1), cend(sentence1),
                                 [](char x) { return x == ' '; }) + 1;
    }

