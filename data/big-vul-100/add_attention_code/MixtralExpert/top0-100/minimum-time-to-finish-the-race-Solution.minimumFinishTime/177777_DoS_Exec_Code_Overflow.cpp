void CairoOutputDev::drawImage(GfxState *state, Object *ref, Stream *str,
				int width, int height,
				GfxImageColorMap *colorMap,
				int *maskColors, GBool inlineImg)
{
  unsigned char *buffer;
  unsigned int *dest;
  cairo_surface_t *image;
  cairo_pattern_t *pattern;
  int x, y;
  ImageStream *imgStr;
  Guchar *pix;
  int i;
   cairo_matrix_t matrix;
   int is_identity_transform;
   
  buffer = (unsigned char *)gmalloc (width * height * 4);
 
   /* TODO: Do we want to cache these? */
   imgStr = new ImageStream(str, width,
			   colorMap->getNumPixelComps(),
			   colorMap->getBits());
  imgStr->reset();
  
  /* ICCBased color space doesn't do any color correction
   * so check its underlying color space as well */
  is_identity_transform = colorMap->getColorSpace()->getMode() == csDeviceRGB ||
		  (colorMap->getColorSpace()->getMode() == csICCBased && 
		   ((GfxICCBasedColorSpace*)colorMap->getColorSpace())->getAlt()->getMode() == csDeviceRGB);

  if (maskColors) {
    for (y = 0; y < height; y++) {
      dest = (unsigned int *) (buffer + y * 4 * width);
      pix = imgStr->getLine();
      colorMap->getRGBLine (pix, dest, width);

      for (x = 0; x < width; x++) {
	for (i = 0; i < colorMap->getNumPixelComps(); ++i) {
	  
	  if (pix[i] < maskColors[2*i] * 255||
	      pix[i] > maskColors[2*i+1] * 255) {
	    *dest = *dest | 0xff000000;
	    break;
	  }
	}
	pix += colorMap->getNumPixelComps();
	dest++;
      }
    }

    image = cairo_image_surface_create_for_data (buffer, CAIRO_FORMAT_ARGB32,
						 width, height, width * 4);
  }
  else {
    for (y = 0; y < height; y++) {
      dest = (unsigned int *) (buffer + y * 4 * width);
      pix = imgStr->getLine();
      colorMap->getRGBLine (pix, dest, width);
    }

    image = cairo_image_surface_create_for_data (buffer, CAIRO_FORMAT_RGB24,
						 width, height, width * 4);
  }

  if (image == NULL) {
   delete imgStr;
   return;
  }
  pattern = cairo_pattern_create_for_surface (image);
  if (pattern == NULL) {
    delete imgStr;
    return;
  }

  LOG (printf ("drawImageMask %dx%d\n", width, height));
  
  cairo_matrix_init_translate (&matrix, 0, height);
  cairo_matrix_scale (&matrix, width, -height);

  cairo_pattern_set_matrix (pattern, &matrix);

  cairo_pattern_set_filter (pattern, CAIRO_FILTER_BILINEAR);
  cairo_set_source (cairo, pattern);
  cairo_paint (cairo);

  if (cairo_shape) {
#if 0
    cairo_rectangle (cairo_shape, 0., 0., width, height);
    cairo_fill (cairo_shape);
#else
    cairo_save (cairo_shape);
    /* this should draw a rectangle the size of the image
     * we use this instead of rect,fill because of the lack
     * of EXTEND_PAD */
    /* NOTE: this will multiply the edges of the image twice */
    cairo_set_source (cairo_shape, pattern);
    cairo_paint(cairo_shape);
    cairo_restore (cairo_shape);
#endif
  }

  cairo_pattern_destroy (pattern);
  cairo_surface_destroy (image);
  free (buffer);
  delete imgStr;
}


    int minimumFinishTime(vector<vector<int>>& tires, int changeTime, int numLaps) {
        static const int INF = numeric_limits<int>::max();

        const auto& ceil_log2 = [](const auto& x) {
            return std::__lg(x - 1) + 1;
        };
        vector<int64_t> dp(ceil_log2(changeTime + 1), INF);  // dp[i]: min time to complete i+1 laps without changing a tire
        for (int i = 0; i < size(tires); ++i) {
            const int f = tires[i][0], r = tires[i][1];
            for (int64_t curr = f, total = f, cnt = 0;
                 curr < changeTime + f;
                 curr *= r, total += curr, ++cnt) {  // at worst (f, r) = (1, 2) => 2^(cnt-1) < changeTime+1 => cnt < ceil(log2(changeTime+1))
                dp[cnt] = min(dp[cnt], total);
            }
        }
        vector<int64_t> dp2(numLaps, INF);  // dp2[i]: min time to complete i+1 laps with changing zero or more tires
        for (int i = 0; i < numLaps; ++i) {
            for (int j = 0; j < min(i + 1, static_cast<int>(size(dp))); ++j) {
                dp2[i] = min(dp2[i], (i - j - 1 >= 0 ? dp2[i - j - 1] + changeTime : 0) + dp[j]);
            }
        }
        return dp2.back();
    }


