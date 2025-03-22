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


    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        static const int MOD = 1e9 + 7;
        uint64_t result = 0, s_sum = 0;
        vector<pair<int, int>> engineers;
        for (int i = 0; i < speed.size(); ++i) {
            engineers.emplace_back(efficiency[i], speed[i]);
        }
        sort(engineers.begin(), engineers.end(), greater<pair<int, int>>());
        priority_queue<int, vector<int>, greater<int>> min_heap;
        for (const auto& [e, s] : engineers) {
            s_sum += s;
            min_heap.emplace(s);
            if (min_heap.size() > k) {
                s_sum -= min_heap.top(); min_heap.pop();
            }
            result = max(result, s_sum * e);
        }
        return result % MOD;
    }


