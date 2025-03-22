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

    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        vector<int> result(size(queries), -1);
        vector<vector<pair<int, int>>> qs(size(heights));
        for (int i = 0; i < size(queries); ++i) {
            int a = queries[i][0], b = queries[i][1];
            if (a > b) {
                swap(a, b);
            }
            if (a == b || heights[a] < heights[b]) {
                result[i] = b;
            } else {
                qs[b].emplace_back(heights[a], i);
            }
        }
        vector<pair<int, int>> stk;
        const auto& binary_search_right = [&](int left, int right, const auto& check) {
            while (left <= right) {
                const int mid = left + (right - left) / 2;
                if (!check(mid)) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return right;
        };

        for (int b = size(heights) - 1; b >= 0; --b) {
            while (!empty(stk) && stk.back().first <= heights[b]) {
                stk.pop_back();
            }
            stk.emplace_back(heights[b], b);
            for (const auto& [ha, i] : qs[b]) {
                const int j = binary_search_right(0, size(stk) - 1, [&, &ha = ha](int x) {
                    return stk[x].first > ha;
                });
                if (j >= 0) {
                    result[i] = stk[j].second;
                }
            }
        }
        return result;
    }

