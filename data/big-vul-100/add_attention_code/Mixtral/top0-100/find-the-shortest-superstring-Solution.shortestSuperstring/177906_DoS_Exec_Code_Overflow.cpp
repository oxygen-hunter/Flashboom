SplashPath *Splash::makeDashedPath(SplashPath *path) {
  SplashPath *dPath;
  SplashCoord lineDashTotal;
  SplashCoord lineDashStartPhase, lineDashDist, segLen;
  SplashCoord x0, y0, x1, y1, xa, ya;
  GBool lineDashStartOn, lineDashOn, newPath;
  int lineDashStartIdx, lineDashIdx;
  int i, j, k;

  lineDashTotal = 0;
  for (i = 0; i < state->lineDashLength; ++i) {
    lineDashTotal += state->lineDash[i];
  }
  if (lineDashTotal == 0) {
    return new SplashPath();
  }
  lineDashStartPhase = state->lineDashPhase;
  i = splashFloor(lineDashStartPhase / lineDashTotal);
  lineDashStartPhase -= (SplashCoord)i * lineDashTotal;
   lineDashStartOn = gTrue;
   lineDashStartIdx = 0;
   if (lineDashStartPhase > 0) {
    while (lineDashStartPhase >= state->lineDash[lineDashStartIdx]) {
       lineDashStartOn = !lineDashStartOn;
       lineDashStartPhase -= state->lineDash[lineDashStartIdx];
       ++lineDashStartIdx;
     }
   }
 
   dPath = new SplashPath();
  while (i < path->length) {

    for (j = i;
	 j < path->length - 1 && !(path->flags[j] & splashPathLast);
	 ++j) ;

    lineDashOn = lineDashStartOn;
    lineDashIdx = lineDashStartIdx;
    lineDashDist = state->lineDash[lineDashIdx] - lineDashStartPhase;

    newPath = gTrue;
    for (k = i; k < j; ++k) {

      x0 = path->pts[k].x;
      y0 = path->pts[k].y;
      x1 = path->pts[k+1].x;
      y1 = path->pts[k+1].y;
      segLen = splashDist(x0, y0, x1, y1);

      while (segLen > 0) {

	if (lineDashDist >= segLen) {
	  if (lineDashOn) {
	    if (newPath) {
	      dPath->moveTo(x0, y0);
	      newPath = gFalse;
	    }
	    dPath->lineTo(x1, y1);
	  }
	  lineDashDist -= segLen;
	  segLen = 0;

	} else {
	  xa = x0 + (lineDashDist / segLen) * (x1 - x0);
	  ya = y0 + (lineDashDist / segLen) * (y1 - y0);
	  if (lineDashOn) {
	    if (newPath) {
	      dPath->moveTo(x0, y0);
	      newPath = gFalse;
	    }
	    dPath->lineTo(xa, ya);
	  }
	  x0 = xa;
	  y0 = ya;
	  segLen -= lineDashDist;
	  lineDashDist = 0;
	}

	if (lineDashDist <= 0) {
	  lineDashOn = !lineDashOn;
	  if (++lineDashIdx == state->lineDashLength) {
	    lineDashIdx = 0;
	  }
	  lineDashDist = state->lineDash[lineDashIdx];
	  newPath = gTrue;
	}
      }
    }
    i = j + 1;
  }
  
  if (dPath->length == 0) {
    GBool allSame = gTrue;
    for (int i = 0; allSame && i < path->length - 1; ++i) {
      allSame = path->pts[i].x == path->pts[i + 1].x && path->pts[i].y == path->pts[i + 1].y;
    }
    if (allSame) {
      x0 = path->pts[0].x;
      y0 = path->pts[0].y;
      dPath->moveTo(x0, y0);
      dPath->lineTo(x0, y0);
    }
  }

  return dPath;
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

