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

    vector<vector<int>> outerTrees(vector<vector<int>>& P) {
        // 3D cross product of OA and OB vectors, (i.e z-component of their "2D" cross product, but remember that it is not defined in "2D").
        // Returns a positive value, if OAB makes a counter-clockwise turn,
        // negative for clockwise turn, and zero if the points are collinear.
        const auto& cross = [](const vector<int>& O, const vector<int>& A, const vector<int>& B) {
            return (A[0] - O[0]) * (B[1] - O[1]) - (A[1] - O[1]) * (B[0] - O[0]);
        };

        // Returns a list of points on the convex hull in counter-clockwise order.
        // Note: the last point in the returned list is the same as the first one.
        size_t n = P.size(), k = 0;
        if (n <= 3) {
            return P;
        }
        vector<vector<int>> H(2*n);

        // Sort points lexicographically
        sort(P.begin(), P.end());

        // Build lower hull
        for (size_t i = 0; i < n; ++i) {
            while (k >= 2 && cross(H[k-2], H[k-1], P[i]) < 0) k--; // modified
            H[k++] = P[i];
        }

        // Build upper hull
        for (size_t i = n-1, t = k+1; i > 0; --i) {
            while (k >= t && cross(H[k-2], H[k-1], P[i-1]) < 0) k--; // modified
            H[k++] = P[i-1];
        }

        H.resize(--k);        
        if (H[1] == H[k - 1]) {  // modified
            H.resize(k / 2 + 1);
        }
        return H;
    }

