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


    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        static const auto& profit = [](double a, double b) {
            return (a + 1) / (b + 1) - a / b;
        };

        vector<tuple<double, int, int>> max_heap;
        for (const auto& c : classes) {
            max_heap.emplace_back(profit(c[0], c[1]), c[0], c[1]);
        }
        make_heap(begin(max_heap), end(max_heap));
        for (; extraStudents > 0; --extraStudents) {
            auto [_, a, b] = max_heap.front();
            ++a, ++b;
            pop_heap(begin(max_heap), end(max_heap)); max_heap.pop_back();
            max_heap.emplace_back(profit(a, b), a, b); push_heap(begin(max_heap), end(max_heap));
        }
        return accumulate(cbegin(max_heap), cend(max_heap), 0.0,
                          [](const auto& total, const auto& x) {
                              return total + float(get<1>(x)) / get<2>(x);
                          }) / size(classes);
    }


