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


    int superpalindromesInRange(string L, string R) {
        const auto K = static_cast<int>(pow(10, (R.length() + 1) * 0.25));
        const int64_t l = stol(L), r = stol(R);
        int result = 0;

        // count odd length
        for (int k = 0; k < K; ++k) {
            const string s = to_string(k), rev_s(s.rbegin(), s.rend());
            int64_t v = stol(s + rev_s.substr(1));
            v *= v;
            if (v > r) {
                break;
            }
            if (v >= l && is_palindrome(v)) {
                ++result;
            }
        }

        // count even length
        for (int k = 0; k < K; ++k) {
            const string s = to_string(k), rev_s(s.rbegin(), s.rend());
            int64_t v = stol(s + rev_s);
            v *= v;
            if (v > r) {
                break;
            }
            if (v >= l && is_palindrome(v)) {
                ++result;
            }
        }

        return result;
    }


