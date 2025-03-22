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


    vector<int> solve(vector<int>& nums, vector<vector<int>>& queries) {
        static const int MOD = 1e9 + 7;
        
        vector<vector<vector<int>>> prefix(floor(sqrt(size(queries))) + 1, vector<vector<int>>(floor(sqrt(size(queries))) + 1));
        vector<int> result;
        for (const auto& query : queries) {
            int x = query[0], y = query[1];
            if (uint64_t(y) * y > size(queries)) {
                int total = 0;
                for (int i = x; i < size(nums); i += y) {
                    total = (total + nums[i]) % MOD;
                }
                result.emplace_back(total);
            } else {
                int begin = x % y;
                if (empty(prefix[begin][y])) {
                    prefix[begin][y].emplace_back(0);
                    for (int i = begin; i < size(nums); i += y) {
                        prefix[begin][y].emplace_back((prefix[begin][y].back() + nums[i]) % MOD);
                    }
                }
                result.emplace_back((prefix[begin][y].back() - prefix[begin][y][x / y] + MOD) % MOD);
            }
        }
        return result;
    }


