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


    vector<long long> countBlackBlocks(int m, int n, vector<vector<int>>& coordinates) {
        static const int L = 2;
    
        unordered_map<int64_t, int> cnt;
        for (const auto& c : coordinates) {
            const int x = c[0], y = c[1];
            for (int nx = max(x - (L - 1), 0); nx < min(x + 1, m - (L - 1)); ++nx) {
                for (int ny = max(y - (L - 1), 0); ny < min(y + 1, n - (L - 1)); ++ny) {
                    ++cnt[static_cast<int64_t>(nx) * n + ny];
                }
            }
        }
        vector<long long> result(L * L + 1);
        for (const auto& [_, c] : cnt) {
            ++result[c];
        }
        result[0] = static_cast<int64_t>(m - (L - 1)) * (n - (L - 1)) - accumulate(cbegin(result) + 1, cend(result), 0ll);
        return result;
    }


