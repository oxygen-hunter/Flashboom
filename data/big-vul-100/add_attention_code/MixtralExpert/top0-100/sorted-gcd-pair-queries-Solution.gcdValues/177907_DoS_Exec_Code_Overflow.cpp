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


    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        unordered_map<int, int> cnt1;
        for (const auto& x : nums) {
            ++cnt1[x];
        }
        vector<int64_t> cnt2(ranges::max(nums) + 1);
        for (int g = size(cnt2) - 1; g >= 1; --g) {
            int64_t c = 0;
            for (int ng = g; ng < size(cnt2); ng += g) {
                c += cnt1[ng];
            }
            cnt2[g] = c * (c - 1) / 2;
            for (int ng = g + g; ng < size(cnt2); ng += g) {
                cnt2[g] -= cnt2[ng];
            }
        }
        vector<int64_t> prefix(size(cnt2) + 1);
        for (int i = 0; i < size(prefix) - 1; ++i) {
            prefix[i + 1] += prefix[i] + cnt2[i];
        }
        vector<int> result(size(queries));
        for (int i = 0; i < size(queries); ++i) {
            result[i] = distance(cbegin(prefix), upper_bound(cbegin(prefix), cend(prefix), queries[i])) - 1;
        }
        return result;
    }


