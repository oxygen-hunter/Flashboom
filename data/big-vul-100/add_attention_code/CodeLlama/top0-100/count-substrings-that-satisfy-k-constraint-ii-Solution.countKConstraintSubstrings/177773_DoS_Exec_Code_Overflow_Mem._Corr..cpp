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


    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) {
        const auto& count = [](int64_t l) {
            return (l + 1) * l / 2;
        };

        vector<int64_t> prefix(size(s) + 1);
        vector<int> lookup(size(s), -1);
        for (int right = 0, left = 0, cnt = 0; right < size(s); ++right) {
            cnt += s[right] == '1' ? 1 : 0;
            while (!(cnt <= k || (right - left + 1) - cnt <= k)) {
                cnt -= s[left++] == '1' ? 1 : 0;
            }
            prefix[right + 1] = prefix[right] + (right - left + 1);
            lookup[left] = right;
        }
        assert(lookup[0] != -1);
        for (int i = 0; i + 1 < size(s); ++i) {
            if (lookup[i + 1] == -1) {
                lookup[i + 1] = lookup[i];
            }
        }
        vector<long long> result(size(queries));
        for (int i = 0; i < size(queries); ++i) {
            const int left = queries[i][0], right = queries[i][1];
            const int new_right = min(lookup[left], right);
            result[i] = count(new_right - left + 1) + (prefix[right + 1] - prefix[new_right + 1]);
        }
        return result;
    }


