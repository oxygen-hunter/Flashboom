void Splash::blitMask(SplashBitmap *src, int xDest, int yDest,
		      SplashClipResult clipRes) {
  SplashPipe pipe;
  Guchar *p;
  int w, h, x, y;
 
   w = src->getWidth();
   h = src->getHeight();
   if (vectorAntialias && clipRes != splashClipAllInside) {
     pipeInit(&pipe, xDest, yDest, state->fillPattern, NULL,
 	     (Guchar)splashRound(state->fillAlpha * 255), gTrue, gFalse);
     drawAAPixelInit();
    p = src->getDataPtr();
     for (y = 0; y < h; ++y) {
       for (x = 0; x < w; ++x) {
 	pipe.shape = *p++;
    pipeInit(&pipe, xDest, yDest, state->fillPattern, NULL,
	     (Guchar)splashRound(state->fillAlpha * 255), gTrue, gFalse);
    p = src->getDataPtr();
   } else {
     pipeInit(&pipe, xDest, yDest, state->fillPattern, NULL,
 	     (Guchar)splashRound(state->fillAlpha * 255), gTrue, gFalse);
    p = src->getDataPtr();
     if (clipRes == splashClipAllInside) {
       for (y = 0; y < h; ++y) {
 	pipeSetXY(&pipe, xDest, yDest + y);
	    (this->*pipe.run)(&pipe);
	  } else {
	    pipeIncX(&pipe);
	  }
	  ++p;
	}
      }
      updateModX(xDest);
      updateModX(xDest + w - 1);
      updateModY(yDest);
      updateModY(yDest + h - 1);
    } else {
      for (y = 0; y < h; ++y) {
	pipeSetXY(&pipe, xDest, yDest + y);
	for (x = 0; x < w; ++x) {
	  if (*p && state->clip->test(xDest + x, yDest + y)) {
	    pipe.shape = *p;
	    (this->*pipe.run)(&pipe);
	    updateModX(xDest + x);
	    updateModY(yDest + y);
	  } else {
	    pipeIncX(&pipe);
	  }
	  ++p;
	}
      }
    }
  }
}

    string shortestSuperstring(vector<string>& A) {
        const int n = A.size();
        vector<vector<int>> overlaps(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int l = min(A[i].length(), A[j].length()); 
                     l >= 0; --l) {
                    if (A[i].substr(A[i].length() - l) == A[j].substr(0, l))  {
                        overlaps[i][j] = l;
                        break;
                    }
                }   
            }
        }
        
        vector<vector<int>> dp(1 << n, vector<int>(n));
        vector<vector<int>> prev(1 << n, vector<int>(n, -1));
        for (int mask = 1; mask < 1 << n; ++mask) {
            for (int bit = 0; bit < n; ++bit) {
                if (((mask >> bit) & 1) == 0) {
                    continue;
                }
                auto prev_mask = mask ^ (1 << bit);
                for (int i = 0; i < n; ++i) {
                    if (((prev_mask >> i) & 1) == 0) {
                        continue;
                    }
                    auto value = dp[prev_mask][i] + overlaps[i][bit];
                    if (value > dp[mask][bit]) {
                        dp[mask][bit] = value;
                        prev[mask][bit] = i;
                    }
                }
            }
        }
        
        int bit = -1;
        for (int i = 0; i < n; ++i) {
            if (bit == -1 ||
                dp.back()[i] > dp.back()[bit]) {
                bit = i;
            }
        }
        vector<int> words;
        for (int mask = (1 << n) - 1; bit != -1;) {
            words.emplace_back(bit);
            tie(mask, bit) = make_pair(mask ^ (1 << bit),
                                       prev[mask][bit]);
        }
        reverse(words.begin(), words.end());
        unordered_set<int> lookup(words.begin(), words.end());
        for (int i = 0; i < n; ++i) {
            if (!lookup.count(i)) {
                words.emplace_back(i);
            }
        }

        auto result = A[words[0]];
        for (int i = 1; i < words.size(); ++i) {
            auto overlap = overlaps[words[i - 1]][words[i]];
            result += A[words[i]].substr(overlap);
        }
        return result;
    }

