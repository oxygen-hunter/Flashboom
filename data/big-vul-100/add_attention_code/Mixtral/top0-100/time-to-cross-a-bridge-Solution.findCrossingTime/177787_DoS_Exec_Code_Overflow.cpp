void SplashOutputDev::drawMaskedImage(GfxState *state, Object *ref,
				      Stream *str, int width, int height,
				      GfxImageColorMap *colorMap,
				      Stream *maskStr, int maskWidth,
				      int maskHeight, GBool maskInvert) {
  GfxImageColorMap *maskColorMap;
  Object maskDecode, decodeLow, decodeHigh;
  double *ctm;
  SplashCoord mat[6];
  SplashOutMaskedImageData imgData;
  SplashOutImageMaskData imgMaskData;
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

  if (maskWidth > width || maskHeight > height) {
    decodeLow.initInt(maskInvert ? 0 : 1);
    decodeHigh.initInt(maskInvert ? 1 : 0);
    maskDecode.initArray(xref);
    maskDecode.arrayAdd(&decodeLow);
    maskDecode.arrayAdd(&decodeHigh);
    maskColorMap = new GfxImageColorMap(1, &maskDecode,
					new GfxDeviceGrayColorSpace());
    maskDecode.free();
    drawSoftMaskedImage(state, ref, str, width, height, colorMap,
			maskStr, maskWidth, maskHeight, maskColorMap);
    delete maskColorMap;

  } else {


    mat[0] = (SplashCoord)width;
    mat[1] = 0;
    mat[2] = 0;
    mat[3] = (SplashCoord)height;
    mat[4] = 0;
    mat[5] = 0;
    imgMaskData.imgStr = new ImageStream(maskStr, maskWidth, 1, 1);
    imgMaskData.imgStr->reset();
    imgMaskData.invert = maskInvert ? 0 : 1;
    imgMaskData.width = maskWidth;
    imgMaskData.height = maskHeight;
    imgMaskData.y = 0;
    maskBitmap = new SplashBitmap(width, height, 1, splashModeMono1, gFalse);
    maskSplash = new Splash(maskBitmap, gFalse);
    maskColor[0] = 0;
    maskSplash->clear(maskColor);
    maskColor[0] = 0xff;
    maskSplash->setFillPattern(new SplashSolidColor(maskColor));
    maskSplash->fillImageMask(&imageMaskSrc, &imgMaskData,
			      maskWidth, maskHeight, mat, gFalse);
    delete imgMaskData.imgStr;
    maskStr->close();
    delete maskSplash;


    ctm = state->getCTM();
    mat[0] = ctm[0];
    mat[1] = ctm[1];
    mat[2] = -ctm[2];
    mat[3] = -ctm[3];
    mat[4] = ctm[2] + ctm[4];
    mat[5] = ctm[3] + ctm[5];

    imgData.imgStr = new ImageStream(str, width,
				     colorMap->getNumPixelComps(),
				     colorMap->getBits());
    imgData.imgStr->reset();
    imgData.colorMap = colorMap;
    imgData.mask = maskBitmap;
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
    splash->drawImage(&maskedImageSrc, &imgData, srcMode, gTrue,
		      width, height, mat);

    delete maskBitmap;
    gfree(imgData.lookup);
    delete imgData.imgStr;
    str->close();
  }
}

    int findCrossingTime(int n, int k, vector<vector<int>>& time) {
        vector<pair<int, int>> workers;
        for (int i = 0; i < k; ++i) {
            workers.emplace_back(time[i][0] + time[i][2], i);
        }
        priority_queue<pair<int, int>> left_bridge(cbegin(workers), cend(workers)), right_bridge;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> left_ware, right_ware;
        int curr = 0;
        while (n) {
            while (!empty(left_ware) && left_ware.top().first <= curr) {
                const auto [_, i] = left_ware.top(); left_ware.pop();
                left_bridge.emplace(time[i][0] + time[i][2], i);
            }
            while (!empty(right_ware) && right_ware.top().first <= curr) {
                const auto [_, i] = right_ware.top(); right_ware.pop();
                right_bridge.emplace(time[i][0] + time[i][2], i);
            }
            if (!empty(right_bridge)) {
                const auto [_, i] = right_bridge.top(); right_bridge.pop();
                curr += time[i][2];
                left_ware.emplace(curr + time[i][3], i);
                --n;
            } else if (!empty(left_bridge) && n - size(right_ware)) {
                const auto [_, i] = left_bridge.top(); left_bridge.pop();
                curr += time[i][0];
                right_ware.emplace(curr + time[i][1], i);
            } else {
                curr = min(!empty(left_ware) ? left_ware.top().first : numeric_limits<int>::max(),
                           !empty(right_ware) ? right_ware.top().first : numeric_limits<int>::max());
            }
        }
        return curr;
    }

