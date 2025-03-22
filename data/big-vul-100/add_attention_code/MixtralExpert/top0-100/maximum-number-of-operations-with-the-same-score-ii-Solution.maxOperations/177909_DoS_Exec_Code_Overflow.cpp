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


    int maxOperations(vector<int>& nums) {
        const function<int (int, int, int, vector<vector<int>>&)> memoization = [&](int left, int right, int target, vector<vector<int>>& lookup) {
            if (!(right - left + 1 >= 2)) {
                return 0;
            }
            if (lookup[left][right] == -1) {
                lookup[left][right] = max({nums[left] + nums[left + 1]   == target ? 1 + memoization(left + 2, right - 0, target, lookup) : 0,
                                           nums[left] + nums[right]      == target ? 1 + memoization(left + 1, right - 1, target, lookup) : 0,
                                           nums[right - 1] + nums[right] == target ? 1 + memoization(left + 0, right - 2, target, lookup) : 0});
            }
            return lookup[left][right];
        };

        int result = 0;
        for (const auto& target : unordered_set<int>{nums[0] + nums[1], nums[0] + nums[size(nums) - 1], nums[size(nums) - 2] + nums[size(nums) - 1]}) {
            vector<vector<int>> lookup(size(nums), vector<int>(size(nums), -1));
            result = max(result, memoization(0, size(nums) - 1, target, lookup));
        }
        return result;
    }


