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


    int shortestSubarray(vector<int>& A, int K) {
        vector<int> accumulated_sum(A.size() + 1, 0);
        partial_sum(A.cbegin(), A.cend(), next(accumulated_sum.begin()), plus<int>());
        
        int result = numeric_limits<int>::max();
        deque<int> mono_increasing_q;
        for (int i = 0; i < accumulated_sum.size(); ++i) {
            while (!mono_increasing_q.empty() &&
                   accumulated_sum[i] <= accumulated_sum[mono_increasing_q.back()]) {
                mono_increasing_q.pop_back();
            }
            while (!mono_increasing_q.empty() &&
                   accumulated_sum[i] - accumulated_sum[mono_increasing_q.front()] >= K) {
                result = min(result, i - mono_increasing_q.front());
                mono_increasing_q.pop_front();
            }
            mono_increasing_q.emplace_back(i);
        }
        return result != numeric_limits<int>::max() ? result : -1;
    }


