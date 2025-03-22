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

    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        static const vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> min_heap;
        min_heap.emplace(grid[0][0], 0, 0);
        vector<vector<bool>> lookup(size(grid), vector<bool>(size(grid[0])));
        lookup[0][0] = true;
        unordered_map<int, int> cnt;
        int mx = 0;
        while (!empty(min_heap)) {
            const auto [curr, i, j] = min_heap.top(); min_heap.pop();
            mx = max(mx, curr);
            ++cnt[mx];
            for (const auto& [di, dj] : directions) {
                const int ni = i + di, nj = j + dj;
                if (!(0 <= ni && ni < size(grid) &&
                      0 <= nj && nj < size(grid[0]) &&
                      !lookup[ni][nj])) {
                    continue;
                }
                lookup[ni][nj] = true;
                min_heap.emplace(grid[ni][nj], ni, nj);
            }
        }
        vector<int> vals;
        for (const auto& [k, _] : cnt) {
            vals.emplace_back(k);
        }
        sort(begin(vals), end(vals));
        vector<int> prefix(size(vals) + 1);
        for (int i = 0; i < size(vals); ++i) {
            prefix[i + 1] = prefix[i] + cnt[vals[i]];
        }
        vector<int> result(size(queries));
        for (int i = 0; i < size(queries); ++i) {
            result[i] = prefix[distance(cbegin(vals), lower_bound(cbegin(vals), cend(vals), queries[i]))];
        }
        return result;
    }

