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


    string reorderSpaces(string text) {
        // count spaces and words
        int space_count = 0, word_count = 0;
        for (int i = 0; i < size(text); ++i) {
            if (text[i] == ' ') {
                ++space_count;
            } else if (i == 0 || text[i - 1] == ' ') {
                ++word_count;
            }
        }
        // rearrange the spaces to the right
        int left = 0, curr = 0;
        for (int i = 0; i < size(text); ++i) {
            bool has_word = false;
            while (i < size(text) && text[i] != ' ') {
                swap(text[left++], text[i++]);
                has_word = true;
            }
            if (has_word) {
                ++left;  // keep one space
            }
        }
        // rearrange the spaces to the left
        int equal_count = word_count - 1 > 0 ? space_count / (word_count - 1) : 0;
        int extra_count = word_count - 1 > 0 ? space_count % (word_count - 1) : space_count;
        int right = size(text) - 1 - extra_count;
        for (int i = size(text) - 1; i >= 0; --i) {
            bool has_word = false;
            while (i >= 0 && text[i] != ' ') {
                swap(text[right--], text[i--]);
                has_word = true;
            }
            if (has_word) {
                right -= equal_count;  // keep equal_count spaces
            }
        }
        return text;
    }


