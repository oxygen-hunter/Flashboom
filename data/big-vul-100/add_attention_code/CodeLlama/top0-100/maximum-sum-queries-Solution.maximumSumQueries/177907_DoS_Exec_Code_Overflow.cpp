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


    vector<int> maximumSumQueries(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        vector<pair<int, int>> pairs;
        for (int i = 0; i < size(nums1); ++i) {
            pairs.emplace_back(nums1[i], nums2[i]);
        }
        sort(begin(pairs), end(pairs));
        vector<tuple<int, int, int>> sorted_queries;
        for (int i = 0; i < size(queries); ++i) {
            sorted_queries.emplace_back(queries[i][0], queries[i][1], i);
        }
        sort(rbegin(sorted_queries), rend(sorted_queries));
        vector<int> result(size(queries));
        vector<pair<int, int>> stk;
        for (const auto& [x, y, i] : sorted_queries) {
            while (!empty(pairs) && pairs.back().first >= x) {
                const auto [a, b] = pairs.back(); pairs.pop_back();
                while (!empty(stk) && stk.back().second <= a + b) {
                    stk.pop_back();
                }
                if (empty(stk) || stk.back().first < b) {
                    stk.emplace_back(b, a + b);
                }
            }
            const auto it = lower_bound(cbegin(stk), cend(stk), pair(y, 0));
            result[i] = it != cend(stk) ? it->second : -1;
        }
        return result;
    }


