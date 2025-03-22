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


    long long maxPower(vector<int>& stations, int r, int k) {
        const auto& min_power = [&]() {
            int64_t mn = numeric_limits<int64_t>::max();
            int64_t curr = accumulate(cbegin(stations), cbegin(stations) + r, 0ll);
            for (int i = 0; i < size(stations); ++i) {
                if (i + r < size(stations)) {
                    curr += stations[i + r];
                }
                if (i >= r + 1) {
                    curr -= stations[i - (r + 1)];
                }
                mn = min(mn, curr);
            }
            return mn;
        };

        const int64_t mn = min_power();
        const auto& check = [&](int64_t target) {
            vector<int> arr(cbegin(stations), cend(stations));
            int64_t curr = accumulate(cbegin(arr), cbegin(arr) + r, 0ll);
            int cnt = k;
            for (int i = 0; i < size(arr); ++i) {
                if (i + r < size(arr)) {
                    curr += arr[i + r];
                }
                if (i >= r + 1) {
                    curr -= arr[i - (r + 1)];
                }
                if (curr >= target) {
                    continue;
                }
                const auto diff = target - curr;
                if (diff > cnt) {
                    return false;
                }
                cnt -= diff;
                curr += diff;
                if (i + r < size(arr)) {
                    arr[i + r] += diff;
                }
            }
            return true;
        };

        int64_t left = mn, right = mn + k;
        while (left <= right) {
            const auto mid = left + (right - left) / 2;
            if (!check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return right;
    }


