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

    int minimumLines(vector<vector<int>>& points) {
        auto ceil_divide = [](int a, int b) {
            return (a + b - 1) / b;
        };
        unordered_map<tuple<int, int, int>, unordered_set<pair<int, int>, PairHash<int>>, TupleHash<int, int, int>> lookup;
        for (int i = 0; i < size(points); ++i) {
            const int x1 = points[i][0], y1 = points[i][1];
            for (int j = i + 1; j < size(points); ++j) {
                const int x2 = points[j][0], y2 = points[j][1];
                // (x-x1)/(x2-x1) = (y-y1)/(y2-y1)
                // => (y2-y1)x - (x2-x1)y = x1(y2-y1) - y1(x2-x1)
                int a = y2 - y1;
                int b = -(x2 - x1);
                int c = x1 * (y2 - y1) - y1 * (x2 - x1);
                const int g = gcd(gcd(a, b), c);
                a /= g, b /= g, c /= g;
                lookup[{a, b, c}].emplace(x1, y1);
                lookup[{a, b, c}].emplace(x2, y2);
            }
        }
        vector<tuple<int, int, int>> lines;
        for (const auto& [l, p] : lookup) {
            if (size(p) > 2) {  // filter to improve complexity
                lines.emplace_back(l);
            }
        }
        assert(size(lines) <= size(points) / 2);  // 1 extra colinear point per 2 points
        int result = numeric_limits<int>::max();
        const int mask_upper_bound = 1 << size(lines);
        for (int mask = 0; mask < mask_upper_bound; ++mask) {
            unordered_set<pair<int, int>, PairHash<int>> covered;
            for (int i = 0, bit = 1; bit <= mask; bit <<= 1, ++i) {
                if (mask & bit) {
                    for (const auto& x : lookup[lines[i]]) {
                        covered.emplace(x);
                    }
                }
            }
            result = min(result, __builtin_popcount(mask) + ceil_divide(size(points) - size(covered), 2));
        }
        return result;
    }

