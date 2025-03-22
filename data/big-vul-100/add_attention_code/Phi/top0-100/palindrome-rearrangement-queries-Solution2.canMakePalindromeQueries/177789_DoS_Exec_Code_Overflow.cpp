poppler_page_prepare_output_dev (PopplerPage *page,
				 double scale,
				 int rotation,
				 gboolean transparent,
				 OutputDevData *output_dev_data)
{
  CairoOutputDev *output_dev;
  cairo_surface_t *surface;
  double width, height;
  int cairo_width, cairo_height, cairo_rowstride, rotate;
  unsigned char *cairo_data;

  rotate = rotation + page->page->getRotate ();
  if (rotate == 90 || rotate == 270) {
    height = page->page->getCropWidth ();
    width = page->page->getCropHeight ();
  } else {
    width = page->page->getCropWidth ();
    height = page->page->getCropHeight ();
  }

  cairo_width = (int) ceil(width * scale);
  cairo_height = (int) ceil(height * scale);
 
   output_dev = page->document->output_dev;
   cairo_rowstride = cairo_width * 4;
  cairo_data = (guchar *) gmalloc (cairo_height * cairo_rowstride);
   if (transparent)
       memset (cairo_data, 0x00, cairo_height * cairo_rowstride);
   else
      memset (cairo_data, 0xff, cairo_height * cairo_rowstride);

  surface = cairo_image_surface_create_for_data(cairo_data,
						CAIRO_FORMAT_ARGB32,
	  					cairo_width, cairo_height, 
						cairo_rowstride);

  output_dev_data->cairo_data = cairo_data;
  output_dev_data->surface = surface;
  output_dev_data->cairo = cairo_create (surface);
  output_dev->setCairo (output_dev_data->cairo);
}

    vector<bool> canMakePalindromeQueries(string s, vector<vector<int>>& queries) {
        vector<int> prefix(size(s) / 2 + 1);
        vector<vector<int>> prefixs1(size(s) / 2 + 1, vector<int>(26));
        vector<vector<int>> prefixs2(size(s) / 2 + 1, vector<int>(26));
        for (int i = 0; i < size(s) / 2; ++i) {
            const int x = s[i] - 'a', y = s[(size(s) - 1) - i] - 'a';
            prefix[i + 1] = prefix[i] + (x != y ? 1 : 0);
            for (int j = 0; j < 26; ++j) {
                prefixs1[i + 1][j] = prefixs1[i][j] + (j == x ? 1 : 0);
                prefixs2[i + 1][j] = prefixs2[i][j] + (j == y ? 1 : 0);
            }
        }
    
        const auto& check = [&](int left1, int right1, int left2, int right2) {
            const auto& same = [&](int left, int right) {
                for (int i = 0; i < 26; ++i) {
                    if ((prefixs1[right + 1][i] - prefixs1[left][i]) - (prefixs2[right + 1][i] - prefixs1[left][i]) != 0) {
                        return false;
                    }
                }
                return true;
            };

            const auto& min_left = min(left1, left2), &max_left = max(left1, left2);
            const auto& min_right = min(right1, right2), &max_right = max(right1, right2);
            if (!(prefix[min_left] - prefix[0] == 0 && prefix.back() - prefix[max_right + 1] == 0)) {
                return false;
            }
            if (min_right < max_left) {  // non-overlapped
                return prefix[max_left] - prefix[min_right + 1] == 0 && same(min_left, min_right) && same(max_left, max_right);
            }
            // overlapped
            if ((left1 == min_left) == (right1 == max_right)) {  // inside another
                return same(min_left, max_right);
            }
            // not inside another
            auto p1 = &prefixs1, p2 = &prefixs2;
            if (min_left != left1) {
                swap(p1, p2);
            }
            for (int i = 0; i < 26; ++i) {
                const int d1 = ((*p1)[min_right + 1][i] - (*p1)[min_left][i]) - ((*p2)[max_left][i] - (*p2)[min_left][i]);
                const int d2 = ((*p2)[max_right + 1][i] - (*p2)[max_left][i]) - ((*p1)[max_right + 1][i] - (*p1)[min_right + 1][i]);
                if (!(d1 == d2 && d1 >= 0)) {  // test case: s = "aabbba", queries = [[0,1,3,4]]
                    return false;
                }
            }
            return true;
        };
    
        vector<bool> result(size(queries));
        for (int i = 0; i < size(queries); ++i) {
            result[i] = check(queries[i][0], queries[i][1], (size(s) - 1) - queries[i][3], (size(s) - 1) - queries[i][2]);
        }
        return result;
    }

