create_surface_from_thumbnail_data (guchar *data,
				    gint    width,
				    gint    height,
 				    gint    rowstride)
 {
   guchar *cairo_pixels;
   cairo_surface_t *surface;
  static cairo_user_data_key_t key;
   int j;
 
  cairo_pixels = (guchar *)g_malloc (4 * width * height);
  surface = cairo_image_surface_create_for_data ((unsigned char *)cairo_pixels,
						 CAIRO_FORMAT_RGB24,
						 width, height, 4 * width);
  cairo_surface_set_user_data (surface, &key,
			       cairo_pixels, (cairo_destroy_func_t)g_free);
 
   for (j = height; j; j--) {
     guchar *p = data;
     guchar *q = cairo_pixels;
     guchar *end = p + 3 * width;
     while (p < end) {
 #if G_BYTE_ORDER == G_LITTLE_ENDIAN
       q[0] = p[2];
       q[1] = p[1];
       q[2] = p[0];
#else	  
       q[1] = p[0];
       q[2] = p[1];
       q[3] = p[2];
#endif
      p += 3;
      q += 4;
     }
 
     data += rowstride;
    cairo_pixels += 4 * width;
   }
 
   return surface;
}

    long long maximumScore(vector<vector<int>>& grid) {
        vector<int64_t> prefix(size(grid)+ 1);
        for (int i = 0; i < size(grid); ++i) {
            prefix[i + 1] = prefix[i] + grid[i][0];
        }
        // dp[0][i]: the maximum score from 0 to the current column, and the current column has i black cells, without scoring the white cells of the current column
        // dp[1][i]: the maximum score from 0 to the current column, and the current column has i black cells, with scoring the white cells of the current column
        vector<vector<int64_t>> dp(2, vector<int64_t>(size(grid) + 1));
        for (int j = 1; j < size(grid[0]); ++j) {
            vector<int64_t> new_prefix(size(grid)+ 1);
            for (int i = 0; i < size(grid); ++i) {
                new_prefix[i + 1] = new_prefix[i] + grid[i][j];
            }
            vector<vector<int64_t>> new_dp(2, vector<int64_t>(size(grid) + 1));
            for (int i = 0; i <= size(grid); ++i) {
                for (int k = 0; k <= size(grid); ++k) {
                    new_dp[0][i] = max(new_dp[0][i], max(prefix[i] - prefix[k], static_cast<int64_t>(0)) + dp[0][k]);
                    new_dp[1][i] = max(new_dp[1][i], dp[1][k] + max(new_prefix[k] - new_prefix[i], static_cast<int64_t>(0)));
                }
                new_dp[0][i] = max(new_dp[0][i], ranges::max(dp[1]));
                new_dp[1][i] = max(new_dp[1][i], new_dp[0][i]);
            }
            dp = move(new_dp);
            prefix = move(new_prefix);
        }
        return ranges::max(dp[1]);
    }

