void CairoOutputDev::drawMaskedImage(GfxState *state, Object *ref,
				Stream *str, int width, int height,
				GfxImageColorMap *colorMap,
				Stream *maskStr, int maskWidth,
				int maskHeight, GBool maskInvert)
{
  ImageStream *maskImgStr;
  maskImgStr = new ImageStream(maskStr, maskWidth, 1, 1);
  maskImgStr->reset();
 
   int row_stride = (maskWidth + 3) & ~3;
   unsigned char *maskBuffer;
  maskBuffer = (unsigned char *)gmalloc (row_stride * maskHeight);
   unsigned char *maskDest;
   cairo_surface_t *maskImage;
   cairo_pattern_t *maskPattern;
  Guchar *pix;
  int x, y;

  int invert_bit;
  
  invert_bit = maskInvert ? 1 : 0;

  for (y = 0; y < maskHeight; y++) {
    pix = maskImgStr->getLine();
    maskDest = maskBuffer + y * row_stride;
    for (x = 0; x < maskWidth; x++) {
      if (pix[x] ^ invert_bit)
	*maskDest++ = 0;
      else
	*maskDest++ = 255;
    }
  }

  maskImage = cairo_image_surface_create_for_data (maskBuffer, CAIRO_FORMAT_A8,
						 maskWidth, maskHeight, row_stride);

  delete maskImgStr;
  maskStr->close();

  unsigned char *buffer;
  unsigned int *dest;
  cairo_surface_t *image;
  cairo_pattern_t *pattern;
  ImageStream *imgStr;
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

  for (y = 0; y < height; y++) {
    dest = (unsigned int *) (buffer + y * 4 * width);
    pix = imgStr->getLine();
    colorMap->getRGBLine (pix, dest, width);
  }

  image = cairo_image_surface_create_for_data (buffer, CAIRO_FORMAT_RGB24,
						 width, height, width * 4);

  if (image == NULL) {
    delete imgStr;
    return;
  }
  pattern = cairo_pattern_create_for_surface (image);
  maskPattern = cairo_pattern_create_for_surface (maskImage);
  if (pattern == NULL) {
    delete imgStr;
    return;
  }

  LOG (printf ("drawMaskedImage %dx%d\n", width, height));

  cairo_matrix_init_translate (&matrix, 0, height);
  cairo_matrix_scale (&matrix, width, -height);

  /* scale the mask to the size of the image unlike softMask */
  cairo_pattern_set_matrix (pattern, &matrix);
  cairo_pattern_set_matrix (maskPattern, &matrix);

  cairo_pattern_set_filter (pattern, CAIRO_FILTER_BILINEAR);
  cairo_set_source (cairo, pattern);
  cairo_mask (cairo, maskPattern);

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
    cairo_mask (cairo_shape, pattern);
    cairo_restore (cairo_shape);
#endif
  }

  cairo_pattern_destroy (maskPattern);
  cairo_surface_destroy (maskImage);
  cairo_pattern_destroy (pattern);
  cairo_surface_destroy (image);
  free (buffer);
  free (maskBuffer);
  delete imgStr;
}


    long long maxPower(vector<int>& stations, int r, int k) {
        const auto& min_power = [&]() {
            int64_t mn = numeric_limits<int64_t>::max();
            int64_t curr = accumulate(cbegin(stations), cbegin(stations) + r, 0ll);
            for (int i = 0; i < size(stations); ++i) {
                if (i + r < size(stations)) {
                    curr += stations[i + r];
                }
                if (i >= r + 1) {
                    curr -= stations[i - (r + 1)];
                }
                mn = min(mn, curr);
            }
            return mn;
        };

        const int64_t mn = min_power();
        const auto& check = [&](int64_t target) {
            vector<int> arr(cbegin(stations), cend(stations));
            int64_t curr = accumulate(cbegin(arr), cbegin(arr) + r, 0ll);
            int cnt = k;
            for (int i = 0; i < size(arr); ++i) {
                if (i + r < size(arr)) {
                    curr += arr[i + r];
                }
                if (i >= r + 1) {
                    curr -= arr[i - (r + 1)];
                }
                if (curr >= target) {
                    continue;
                }
                const auto diff = target - curr;
                if (diff > cnt) {
                    return false;
                }
                cnt -= diff;
                curr += diff;
                if (i + r < size(arr)) {
                    arr[i + r] += diff;
                }
            }
            return true;
        };

        int64_t left = mn, right = mn + k;
        while (left <= right) {
            const auto mid = left + (right - left) / 2;
            if (!check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return right;
    }


