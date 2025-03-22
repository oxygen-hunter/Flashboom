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


    int minimumSubarrayLength(vector<int>& nums, int k) {
        const auto& bit_length = [](int x) {
            return (x ? std::__lg(x) : -1) + 1;
        };
    
        const int total = accumulate(cbegin(nums), cend(nums), 0, [](const auto& x, const auto& y) {
            return x | y;
        });
        if (total < k) {
            return -1;
        }
        vector<int> cnt(bit_length(total));
        const auto& update = [&](int x, int d, int curr) {
            for (int i = 0; (1 << i) <= x; ++i) {
                if (!(x & (1 << i))) {
                    continue;
                }
                if (cnt[i] == 0) {
                    curr ^= 1 << i;
                }
                cnt[i] += d;
                if (cnt[i] == 0) {
                    curr ^= 1 << i;
                }
            }
            return curr;
        };

        int result = size(nums);
        for (int right = 0, left = 0, curr = 0; right < size(nums); ++right) {
            curr = update(nums[right], +1, curr);
            for (; left <= right && curr >= k; ++left) {
                result = min(result, right - left + 1);
                curr = update(nums[left], -1, curr);
            }
        }
        return result;
    }


