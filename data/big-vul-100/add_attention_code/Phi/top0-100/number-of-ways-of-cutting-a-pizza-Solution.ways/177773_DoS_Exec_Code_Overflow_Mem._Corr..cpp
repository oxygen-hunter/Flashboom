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

    int ways(vector<string>& pizza, int k) {
        static int MOD = 1e9 + 7;
        vector<vector<int>> prefix(pizza.size(), vector<int>(pizza[0].size()));
        for (int j = pizza[0].size() - 1; j >= 0; --j) {
            for (int accu = 0, i = pizza.size() - 1; i >= 0; --i) {
                accu += pizza[i][j] == 'A';
                prefix[i][j] = ((j + 1 != pizza[0].size()) ? prefix[i][j + 1] : 0) + accu;
            }
        }
        vector<vector<vector<uint64_t>>> dp(pizza.size(),
                                            vector<vector<uint64_t>>(pizza[0].size(),
                                            vector<uint64_t>(k)));
        for (int i = pizza.size() - 1; i >= 0; --i) {
            for (int j = pizza[0].size() - 1; j >= 0; --j) {
                dp[i][j][0] = 1;
                for (int m = 1; m < k; ++m) {
                    for (int n = i + 1; n < pizza.size() && prefix[n][j]; ++n) {
                        if (prefix[i][j] == prefix[n][j]) {
                            continue;
                        }
                        dp[i][j][m] = (dp[i][j][m] + dp[n][j][m - 1]) % MOD;
                    }
                    for (int n = j + 1; n < pizza[0].size() && prefix[i][n]; ++n) {
                        if (prefix[i][j] == prefix[i][n]) {
                            continue;
                        }
                        dp[i][j][m] = (dp[i][j][m] + dp[i][n][m - 1]) % MOD;
                    }
                }
            }
        }
        return dp[0][0][k - 1];
    }

