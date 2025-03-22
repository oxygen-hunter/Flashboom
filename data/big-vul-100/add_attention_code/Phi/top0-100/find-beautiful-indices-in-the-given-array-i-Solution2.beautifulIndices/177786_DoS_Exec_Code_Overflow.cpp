void SplashOutputDev::drawImage(GfxState *state, Object *ref, Stream *str,
				int width, int height,
				GfxImageColorMap *colorMap,
				int *maskColors, GBool inlineImg) {
  double *ctm;
  SplashCoord mat[6];
  SplashOutImageData imgData;
  SplashColorMode srcMode;
  SplashImageSource src;
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

  imgData.imgStr = new ImageStream(str, width,
				   colorMap->getNumPixelComps(),
				   colorMap->getBits());
  imgData.imgStr->reset();
  imgData.colorMap = colorMap;
  imgData.maskColors = maskColors;
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
      break;
    }
  }

  if (colorMode == splashModeMono1) {
    srcMode = splashModeMono8;
  } else {
    srcMode = colorMode;
  }
  src = maskColors ? &alphaImageSrc : &imageSrc;
  splash->drawImage(src, &imgData, srcMode, maskColors ? gTrue : gFalse,
		    width, height, mat);
  if (inlineImg) {
    while (imgData.y < height) {
      imgData.imgStr->getLine();
      ++imgData.y;
    }
  }

  gfree(imgData.lookup);
  delete imgData.imgStr;
  str->close();
}

    vector<int> beautifulIndices(string s, string a, string b, int k) {
        const auto& KMP = [&](const string& text, const string& pattern) {
            const auto& getPrefix = [&](const string& pattern) {
                vector<int> prefix(pattern.length(), -1);
                int j = -1;
                for (int i = 1; i < pattern.length(); ++i) {
                    while (j > -1 && pattern[j + 1] != pattern[i]) {
                        j = prefix[j];
                    }
                    if (pattern[j + 1] == pattern[i]) {
                        ++j;
                    }
                    prefix[i] = j;
                }
                return prefix;
            };

            vector<int> result;
            const vector<int> prefix = getPrefix(pattern + '#' + text);
            for (int i = (size(pattern) + 1) + (size(pattern) - 1); i < size(prefix); ++i) {
                if (prefix[i] + 1 == size(pattern)) {
                    result.emplace_back((i - (size(pattern) + 1)) - (size(pattern) - 1));
                }
            }
            return result;
        };

        vector<int> result;
        if (!(size(a) <= size(s) && size(b) <= size(s))) {
            return result;
        }
        const auto& lookup = KMP(s, b);
        int j = 0;
        for (const auto& i : KMP(s, a)) {
            const int j = distance(cbegin(lookup), lower_bound(cbegin(lookup), cend(lookup), i - k));
            if (j < size(lookup) && lookup[j] <= i + k) {
                result.emplace_back(i);
            }
        }
        return result;
    }

