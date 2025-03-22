void CairoOutputDev::drawSoftMaskedImage(GfxState *state, Object *ref, Stream *str,
				int width, int height,
				GfxImageColorMap *colorMap,
				Stream *maskStr,
				int maskWidth, int maskHeight,
				GfxImageColorMap *maskColorMap)
{
  ImageStream *maskImgStr;
  maskImgStr = new ImageStream(maskStr, maskWidth,
				       maskColorMap->getNumPixelComps(),
				       maskColorMap->getBits());
  maskImgStr->reset();
 
   int row_stride = (maskWidth + 3) & ~3;
   unsigned char *maskBuffer;
  maskBuffer = (unsigned char *)gmalloc (row_stride * maskHeight);
   unsigned char *maskDest;
   cairo_surface_t *maskImage;
   cairo_pattern_t *maskPattern;
  Guchar *pix;
  int y;
  for (y = 0; y < maskHeight; y++) {
    maskDest = (unsigned char *) (maskBuffer + y * row_stride);
    pix = maskImgStr->getLine();
    maskColorMap->getGrayLine (pix, maskDest, maskWidth);
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
   cairo_matrix_t maskMatrix;
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

  LOG (printf ("drawSoftMaskedImage %dx%d\n", width, height));

  cairo_matrix_init_translate (&matrix, 0, height);
  cairo_matrix_scale (&matrix, width, -height);

  cairo_matrix_init_translate (&maskMatrix, 0, maskHeight);
  cairo_matrix_scale (&maskMatrix, maskWidth, -maskHeight);

  cairo_pattern_set_matrix (pattern, &matrix);
  cairo_pattern_set_matrix (maskPattern, &maskMatrix);

  cairo_pattern_set_filter (pattern, CAIRO_FILTER_BILINEAR);
  cairo_pattern_set_filter (maskPattern, CAIRO_FILTER_BILINEAR);
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

    long long getMaxFunctionValue(vector<int>& receiver, long long k) {
        const auto& find_cycles = [](const auto& adj) {
            vector<pair<int, int>> result;
            vector<int> lookup(size(adj));
            for (int i = 0, idx = 0; i < size(adj); ++i) {
                int u = i, prev = idx;
                while (!lookup[u]) {
                    lookup[u] = ++idx;
                    u = adj[u];
                }
                if (lookup[u] > prev) {
                    result.emplace_back(u, idx - lookup[u] + 1);
                }
            }
            return result;
        };
        
        const auto& cycles = find_cycles(receiver);
        vector<pair<int, int>> lookup(size(receiver), {-1, -1});
        vector<vector<int64_t>> prefixes(size(cycles), vector<int64_t>(1));
        const auto& find_prefixes = [&](const auto& cycles) {
            for (int idx = 0; idx < size(cycles); ++idx) {
                auto [u, l] = cycles[idx];
                for (int i = 0; i < l; ++i) {
                    lookup[u] = {idx, i};
                    prefixes[idx].emplace_back(prefixes[idx][i] + u);
                    u = receiver[u];
                }
            }
        };
        
        const auto& get_sum = [](const auto& prefix, int64_t i, int64_t cnt) {
            const int64_t l = size(prefix) - 1;
            const int64_t q = cnt / l;
            const int64_t r = cnt % l;
            return (q * prefix.back() +
                    (prefix[min(i + r, l)] - prefix[i]) +
                    (prefix[max((i + r) - l, static_cast<int64_t>(0))] - prefix[0]));
        };
        
        const auto& start_inside_cycle = [&]() {
            int64_t result = 0;
            for (auto [u, l] : cycles) {
                for (int _ = 0; _ < l; ++_) {
                    const auto& [idx, i] = lookup[u];
                    result = max(result, get_sum(prefixes[idx], i, k + 1));
                    u = receiver[u];
                }
            }
            return result;
        };
    
        const auto& start_outside_cycle = [&]() {
            int64_t result = 0;
            vector<int> degree(size(receiver));
            for (const auto& x : receiver) {
                ++degree[x];
            }
            for (int u = 0; u < size(receiver); ++u) {
                if (degree[u]) {
                    continue;
                }
                int64_t curr = 0;
                deque<int> dq;
                int v = u;
                while (lookup[v].first == -1) {
                    curr += v;
                    dq.emplace_back(v);
                    if (size(dq) == k + 1) {
                        result = max(result, curr);
                        curr -= dq.front(); dq.pop_front();
                    }
                    v = receiver[v];
                }
                const auto& [idx, i] = lookup[v];
                while (!empty(dq)) {
                    result = max(result, curr + get_sum(prefixes[idx], i, (k + 1) - size(dq)));
                    curr -= dq.front(); dq.pop_front();
                }
            }
            return result;
        };
              
        find_prefixes(cycles);
        return max(start_inside_cycle(), start_outside_cycle());
    }

