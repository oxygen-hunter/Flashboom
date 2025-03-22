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


    int minimumDistance(vector<vector<int>>& points) {
        const auto& max_distance = [&](int exclude) {
            static const int POS_INF = numeric_limits<int>::max();
            static const int NEG_INF = numeric_limits<int>::min();
    
            pair<int, int> max_sum = {NEG_INF, -1};
            pair<int, int> min_sum = {POS_INF, -1};
            pair<int, int> max_diff = {NEG_INF, -1};
            pair<int, int> min_diff = {POS_INF, -1};
            for (int i = 0; i < size(points); ++i) {
                if (i == exclude) {
                    continue;
                }
                const int x = points[i][0], y = points[i][1];
                max_sum = max(max_sum, {x + y, i});
                min_sum = min(min_sum, {x + y, i});
                max_diff = max(max_diff, {x - y, i});
                min_diff = min(min_diff, {x - y, i});
            }
            return max(tuple{max_sum.first - min_sum.first, max_sum.second, min_sum.second},
                       tuple{max_diff.first - min_diff.first, max_diff.second, min_diff.second});
        };
    
        const auto& [_, i, j] = max_distance(-1);
        return min(get<0>(max_distance(i)), get<0>(max_distance(j)));
    }


