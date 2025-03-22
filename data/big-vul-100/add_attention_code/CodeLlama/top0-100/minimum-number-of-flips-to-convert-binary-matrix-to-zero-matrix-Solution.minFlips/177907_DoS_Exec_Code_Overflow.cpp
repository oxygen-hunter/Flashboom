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


    int minFlips(vector<vector<int>>& mat) {
        static const vector<pair<int, int>> directions{{0, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int start = 0;
        for (int r = 0; r < mat.size(); ++r) {
            for (int c = 0; c < mat[0].size(); ++c) {
                start |= mat[r][c] << r * mat[0].size() + c;
            }
        }
        queue<pair<int, int>> q({{start, 0}});
        unordered_set<int> lookup = {start};
        while (!q.empty()) {
            const auto [state, step] = q.front(); q.pop();
            if (!state) {
                return step;
            }
            for (int r = 0; r < mat.size(); ++r) {
                for (int c = 0; c < mat[0].size(); ++c) {
                    int new_state = state;
                    for (const auto& [dr, dc] : directions) {
                        const auto& [nr, nc] = make_pair(r + dr, c + dc);
                        if (0 <= nr && nr < mat.size() &&
                            0 <= nc && nc < mat[0].size()) {
                            new_state ^= 1 << nr * mat[0].size() + nc;
                        }
                    }
                    if (lookup.count(new_state)) {
                        continue;
                    }
                    lookup.emplace(new_state);
                    q.emplace(new_state, step + 1);
                 }
            }
        }
        return -1;
    }


