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


    long long singleDivisorTriplet(vector<int>& nums) {
        const auto& check = [](int a, int b, int c) {
            const int total = a + b + c;
            return (total % a == 0) + (total % b == 0) + (total % c == 0) == 1;
        };
        unordered_map<int, int64_t> cnt;
        for (const auto& x : nums) {
            ++cnt[x];
        }
        vector<int> unique_nums;
        for (const auto& [k, _] : cnt) {
            unique_nums.emplace_back(k);
        }
        int64_t result = 0;
        for (int i = 0; i < size(unique_nums); ++i) {
            for (int j = i + 1; j < size(unique_nums); ++j) {
                for (int k = j + 1; k < size(unique_nums); ++k) {
                    if (check(unique_nums[i], unique_nums[j], unique_nums[k])) {
                        result += cnt[unique_nums[i]] * cnt[unique_nums[j]] * cnt[unique_nums[k]];
                    }
                }
            }
        }
        for (int i = 0; i < size(unique_nums); ++i) {
            for (int j = 0; j < size(unique_nums); ++j) {
                if (check(unique_nums[i], unique_nums[i], unique_nums[j])) {
                    result += cnt[unique_nums[i]] * (cnt[unique_nums[i]] - 1) / 2 * cnt[unique_nums[j]];
                }
            }
        }
        return result * 6;
    }


