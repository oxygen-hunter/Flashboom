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

    int minimumTimeToInitialState(string word, int k) {
        const auto& ceil_divide = [](int a, int b) {
            return (a + b - 1) / b;
        };

        // Template: https://cp-algorithms.com/string/z-function.html
        const auto& z_function = [](const string& s) {  // Time: O(n), Space: O(n)
            vector<int> z(size(s));
            for (int i = 1, l = 0, r = 0; i < size(z); ++i) {
                if (i <= r) {
                    z[i] = min(r - i + 1, z[i - l]);
                }
                while (i + z[i] < size(z) && s[z[i]] == s[i + z[i]]) {
                    ++z[i];
                }
                if (i + z[i] - 1 > r) {
                    l = i, r = i + z[i] - 1;
                }
            }
            return z;
        };

        const auto& z = z_function(word);
        for (int i = k; i < size(word); i += k) {
            if (z[i] == size(word) - i) {
                return i / k;
            }
        }
        return ceil_divide(size(word), k);
    }

