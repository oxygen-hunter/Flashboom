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


    vector<int> maximumSumQueries(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        vector<pair<int, int>> pairs;
        for (int i = 0; i < size(nums1); ++i) {
            pairs.emplace_back(nums1[i], nums2[i]);
        }
        sort(begin(pairs), end(pairs));
        vector<tuple<int, int, int>> sorted_queries;
        for (int i = 0; i < size(queries); ++i) {
            sorted_queries.emplace_back(queries[i][0], queries[i][1], i);
        }
        sort(rbegin(sorted_queries), rend(sorted_queries));
        vector<int> result(size(queries));
        vector<pair<int, int>> stk;
        for (const auto& [x, y, i] : sorted_queries) {
            while (!empty(pairs) && pairs.back().first >= x) {
                const auto [a, b] = pairs.back(); pairs.pop_back();
                while (!empty(stk) && stk.back().second <= a + b) {
                    stk.pop_back();
                }
                if (empty(stk) || stk.back().first < b) {
                    stk.emplace_back(b, a + b);
                }
            }
            const auto it = lower_bound(cbegin(stk), cend(stk), pair(y, 0));
            result[i] = it != cend(stk) ? it->second : -1;
        }
        return result;
    }


