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


    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>> dist(n, vector<int>(n, numeric_limits<int>::max()));
        for (const auto& e : edges) {
            dist[e[0]][e[1]] = dist[e[1]][e[0]] = e[2];
        }
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
        }
        for (int k = 0; k < n; ++k) {
             for (int i = 0; i < n; ++i) {
                 for (int j = 0; j < n; ++j) {
                     if (dist[i][k] != numeric_limits<int>::max() &&
                         dist[k][j] != numeric_limits<int>::max()) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                     }
                 }
             }
        }
        int result = -1, min_num = numeric_limits<int>::max();
        for (int i = n - 1; i >= 0; --i) {
            int num = accumulate(dist[i].cbegin(), dist[i].cend(), 0,
                                 [&distanceThreshold](const auto& a, const auto& b) {
                                     return a + (b <= distanceThreshold);
                                 });
            if (num < min_num) {
                min_num = num;
                result = i;
            }
        }
        return result;
    }


