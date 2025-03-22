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


    TreeNode* findNeartestRightNode(TreeNode* root, TreeNode* u) {
        vector<TreeNode *> q = {root};
        while (!empty(q)) {
            vector<TreeNode *> new_q;
            for (int i = 0; i < size(q); ++i) {
                if (q[i] == u) {
                    return i + 1 < size(q) ? q[i + 1] : nullptr;
                }
                if (q[i]->left) {
                    new_q.emplace_back(q[i]->left);
                }
                if (q[i]->right) {
                    new_q.emplace_back(q[i]->right);
                }
            }
            q = move(new_q);
        }
        return nullptr;
    }


