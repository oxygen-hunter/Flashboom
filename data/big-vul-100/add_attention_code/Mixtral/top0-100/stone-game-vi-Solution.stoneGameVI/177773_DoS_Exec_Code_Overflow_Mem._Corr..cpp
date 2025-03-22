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

    int stoneGameVI(vector<int>& aliceValues, vector<int>& bobValues) {
        vector<vector<int>> sorted_vals;
        vector<int> result(2);
        for (int i = 0; i < size(aliceValues); ++i) {
            sorted_vals.push_back({aliceValues[i] + bobValues[i],
                                   aliceValues[i], bobValues[i]});
        }
        sort(begin(sorted_vals), end(sorted_vals), greater<vector<int>>());
        for (int i = 0; i < size(sorted_vals); ++i) {
            result[i % 2] += sorted_vals[i][1 + i % 2];
        }
        return (result[0] == result[1]) ? 0 : (result[0] > result[1]) ? 1 : -1;
    }

