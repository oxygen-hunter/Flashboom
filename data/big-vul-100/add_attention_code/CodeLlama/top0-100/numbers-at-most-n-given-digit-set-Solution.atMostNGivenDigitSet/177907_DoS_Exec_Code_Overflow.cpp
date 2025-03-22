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


    int atMostNGivenDigitSet(vector<string>& D, int N) {
        string str_N = to_string(N);
        unordered_set<string> set_D(D.cbegin(), D.cend());
        int result = 0;
        for (int i = 1 ; i < str_N.length() ; ++i) {
            result += pow(D.size(), i);  // x, xx, xxx
        }
        int i = 0;
        // assume N = 1234, D = 1, 2, 3, 4
        for (i = 0 ; i < str_N.length() ; ++i) {
            for (const auto& d : D) {
                if (d[0] < str_N[i]) {
                    // 11xx; 121x, 122x; 1231, 1232, 1233;
                    result += pow(D.size(), str_N.length() - i - 1);
                } else {
                    break;
                }
            }
            if (!set_D.count(string(1, str_N[i]))) {
                break;
            }
        }               
        return result + int(i == str_N.length());  // 1234
    }


