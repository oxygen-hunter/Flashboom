void SplashOutputDev::drawSoftMaskedImage(GfxState *state, Object *ref,
					  Stream *str, int width, int height,
					  GfxImageColorMap *colorMap,
					  Stream *maskStr,
					  int maskWidth, int maskHeight,
					  GfxImageColorMap *maskColorMap) {
  double *ctm;
  SplashCoord mat[6];
  SplashOutImageData imgData;
  SplashOutImageData imgMaskData;
  SplashColorMode srcMode;
  SplashBitmap *maskBitmap;
  Splash *maskSplash;
  SplashColor maskColor;
  GfxGray gray;
  GfxRGB rgb;
#if SPLASH_CMYK
  GfxCMYK cmyk;
#endif
  Guchar pix;
  int n, i;

  ctm = state->getCTM();
  mat[0] = ctm[0];
  mat[1] = ctm[1];
  mat[2] = -ctm[2];
  mat[3] = -ctm[3];
  mat[4] = ctm[2] + ctm[4];
  mat[5] = ctm[3] + ctm[5];


  imgMaskData.imgStr = new ImageStream(maskStr, maskWidth,
				       maskColorMap->getNumPixelComps(),
				       maskColorMap->getBits());
  imgMaskData.imgStr->reset();
  imgMaskData.colorMap = maskColorMap;
  imgMaskData.maskColors = NULL;
  imgMaskData.colorMode = splashModeMono8;
  imgMaskData.width = maskWidth;
  imgMaskData.height = maskHeight;
  imgMaskData.y = 0;
  n = 1 << maskColorMap->getBits();
  imgMaskData.lookup = (SplashColorPtr)gmalloc(n);
  for (i = 0; i < n; ++i) {
    pix = (Guchar)i;
    maskColorMap->getGray(&pix, &gray);
    imgMaskData.lookup[i] = colToByte(gray);
  }
  maskBitmap = new SplashBitmap(bitmap->getWidth(), bitmap->getHeight(),
				1, splashModeMono8, gFalse);
  maskSplash = new Splash(maskBitmap, vectorAntialias);
  maskColor[0] = 0;
  maskSplash->clear(maskColor);
  maskSplash->drawImage(&imageSrc, &imgMaskData, splashModeMono8, gFalse,
			maskWidth, maskHeight, mat);
  delete imgMaskData.imgStr;
  maskStr->close();
  gfree(imgMaskData.lookup);
  delete maskSplash;
  splash->setSoftMask(maskBitmap);


  imgData.imgStr = new ImageStream(str, width,
				   colorMap->getNumPixelComps(),
				   colorMap->getBits());
  imgData.imgStr->reset();
  imgData.colorMap = colorMap;
  imgData.maskColors = NULL;
  imgData.colorMode = colorMode;
  imgData.width = width;
  imgData.height = height;
  imgData.y = 0;

  imgData.lookup = NULL;
  if (colorMap->getNumPixelComps() == 1) {
    n = 1 << colorMap->getBits();
    switch (colorMode) {
    case splashModeMono1:
    case splashModeMono8:
      imgData.lookup = (SplashColorPtr)gmalloc(n);
      for (i = 0; i < n; ++i) {
	pix = (Guchar)i;
	colorMap->getGray(&pix, &gray);
	imgData.lookup[i] = colToByte(gray);
      }
       break;
     case splashModeRGB8:
     case splashModeBGR8:
      imgData.lookup = (SplashColorPtr)gmalloc(3 * n);
       for (i = 0; i < n; ++i) {
 	pix = (Guchar)i;
 	colorMap->getRGB(&pix, &rgb);
	imgData.lookup[3*i] = colToByte(rgb.r);
	imgData.lookup[3*i+1] = colToByte(rgb.g);
	imgData.lookup[3*i+2] = colToByte(rgb.b);
       }
       break;
     case splashModeXBGR8:
      imgData.lookup = (SplashColorPtr)gmalloc(4 * n);
       for (i = 0; i < n; ++i) {
 	pix = (Guchar)i;
 	colorMap->getRGB(&pix, &rgb);
	imgData.lookup[4*i] = colToByte(rgb.r);
	imgData.lookup[4*i+1] = colToByte(rgb.g);
	imgData.lookup[4*i+2] = colToByte(rgb.b);
	imgData.lookup[4*i+3] = 255;
      }
       break;
 #if SPLASH_CMYK
     case splashModeCMYK8:
      imgData.lookup = (SplashColorPtr)gmalloc(4 * n);
       for (i = 0; i < n; ++i) {
 	pix = (Guchar)i;
 	colorMap->getCMYK(&pix, &cmyk);
	imgData.lookup[4*i] = colToByte(cmyk.c);
	imgData.lookup[4*i+1] = colToByte(cmyk.m);
	imgData.lookup[4*i+2] = colToByte(cmyk.y);
	imgData.lookup[4*i+3] = colToByte(cmyk.k);
      }
      break;
#endif
    }
  }

  if (colorMode == splashModeMono1) {
    srcMode = splashModeMono8;
  } else {
    srcMode = colorMode;
  }
  splash->drawImage(&imageSrc, &imgData, srcMode, gFalse, width, height, mat);

  splash->setSoftMask(NULL);
  gfree(imgData.lookup);
  delete imgData.imgStr;
  str->close();
}


    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        const auto R = board.size(), C = board[0].size();
        bool changed = true;
        
        while (changed) {
            changed = false;
            
            for (int r = 0; r < R; ++r) {
                for (int c = 0; c + 2 < C; ++c) {
                    auto v = abs(board[r][c]);
                    if (v != 0 && v == abs(board[r][c + 1]) && v == abs(board[r][c + 2])) {
                        board[r][c] = board[r][c + 1] = board[r][c + 2] = -v;
                        changed = true;
                    }
                }
            }
            
            for (int r = 0; r + 2 < R; ++r) {
                for (int c = 0; c < C; ++c) {
                    auto v = abs(board[r][c]);
                    if (v != 0 && v == abs(board[r + 1][c]) && v == abs(board[r + 2][c])) {
                        board[r][c] = board[r + 1][c] = board[r + 2][c] = -v;
                        changed = true;
                    }
                }
            }

            for (int c = 0; c < C; ++c) {
                int empty_r = R - 1;
                for (int r = R - 1; r >= 0; --r) {
                    if (board[r][c] > 0) {
                        board[empty_r--][c] = board[r][c];
                    }
                }
                for (int r = empty_r; r >= 0; --r) {
                    board[r][c] = 0;
                }
            }
        }
        
        return board;
    }


