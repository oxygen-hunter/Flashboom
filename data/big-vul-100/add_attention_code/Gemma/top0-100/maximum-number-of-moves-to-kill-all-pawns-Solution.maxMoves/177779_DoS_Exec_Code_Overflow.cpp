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


    int maxMoves(int kx, int ky, vector<vector<int>>& positions) {
        static const int N = 50;
        static const vector<pair<int, int>> DIRECTIONS = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};
        static const int POS_INF = numeric_limits<int>::max();
        static const int NEG_INF = numeric_limits<int>::min();

        const auto& bfs = [](int r, int c) {
            vector<vector<int>> dist(N, vector<int>(N, POS_INF));
            dist[r][c] = 0;
            vector<pair<int, int>> q = {{r, c}};
            while (!empty(q)) {
                vector<pair<int, int>> new_q;
                for (const auto& [r, c] : q) {
                    for (const auto& [dr, dc] : DIRECTIONS) {
                        const int nr = r + dr, nc = c + dc;
                        if (!(0 <= nr && nr < N && 0 <= nc && nc < N && dist[nr][nc] == POS_INF)) {
                            continue;
                        }
                        dist[nr][nc] = dist[r][c] + 1;
                        new_q.emplace_back(nr, nc);
                    }
                }
                q = move(new_q);
            }
            return dist;
        };

        const int p = size(positions);
        positions.emplace_back(vector<int>{kx, ky});
        vector<vector<int>> dist(p + 1, vector<int>(p + 1));
        for (int i = 0; i <= p; ++i) {
            const auto& d = bfs(positions[i][0], positions[i][1]);
            for (int j = i + 1; j <= p; ++j) {
                dist[j][i] = dist[i][j] = d[positions[j][0]][positions[j][1]];
            }
        }
        vector<vector<int>> dp(1 << p);
        for (int mask = 1; mask < 1 << p; ++mask) {
            dp[mask].assign(p, __builtin_popcount(mask) & 1 ? POS_INF : NEG_INF);
        }
        dp.back().assign(p, 0);
        for (int mask = (1 << p) - 1; mask >= 1; --mask) {
            const auto& turn = (__builtin_popcount(mask) & 1) ^ 1;
            for (int i = 0; i < p; ++i) {
                if ((mask & (1 << i)) == 0) {
                    continue;
                }
                for (int j = 0; j < p; ++j) {
                    if (j == i || (mask & (1 << j)) == 0) {
                        continue;
                    }
                    dp[mask ^ (1 << i)][j] = turn ? min(dp[mask ^ (1 << i)][j], dp[mask][i] + dist[i][j])
                                                  : max(dp[mask ^ (1 << i)][j], dp[mask][i] + dist[i][j]);
                }
            }
        }
        int result = 0;
        for (int i = 0; i < p; ++i) {
            result = max(result, dp[1 << i][i] + dist[i][p]);
        }
        return result;
    }


