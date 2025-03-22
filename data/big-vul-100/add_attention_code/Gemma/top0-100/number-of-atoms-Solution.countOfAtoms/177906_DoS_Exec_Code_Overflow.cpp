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


    string countOfAtoms(string formula) {
        stack<map<string, int>> stk;
        stk.emplace();
        int submatches[] = { 1, 2, 3, 4, 5 };
        const auto e = regex("([A-Z][a-z]*)(\\d*)|(\\()|(\\))(\\d*)");
        for (regex_token_iterator<string::iterator> it(formula.begin(), formula.end(), e, submatches), end;
             it != end;) {
            const auto& name = (it++)->str();
            const auto& m1 = (it++)->str();
            const auto& left_open = (it++)->str();
            const auto& right_open = (it++)->str();
            const auto& m2 = (it++)->str();
            if (!name.empty()) {
                stk.top()[name] += stoi(!m1.empty() ? m1 : "1");
            }
            if (!left_open.empty()) {
                stk.emplace();
            }
            if (!right_open.empty()) {
                const auto top = move(stk.top()); stk.pop();
                for (const auto& kvp: top) {
                    stk.top()[kvp.first] += kvp.second * stoi(!m2.empty() ? m2 : "1");
                }
            }
        }
        string result;
        for (const auto& kvp : stk.top()) {
            result += kvp.first;
            if (kvp.second > 1) {
                result += to_string(kvp.second);
            }
        }
        return result;
    }


