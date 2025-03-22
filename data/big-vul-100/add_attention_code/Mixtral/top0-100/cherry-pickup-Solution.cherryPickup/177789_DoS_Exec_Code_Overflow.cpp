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

    int cherryPickup(vector<vector<int>>& grid) {
        // dp holds the max # of cherries two k-length paths can pickup.
        // The two k-length paths arrive at (i, k - i) and (j, k - j), 
        // respectively.
        const int n = grid.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        dp[0][0] = grid[0][0];

        const int max_len = 2 * (n - 1);
        for (int k = 1; k <= max_len; ++k) {
            for (int i = min(k, n - 1); i >= max(0, k - n + 1); --i) {  // 0 <= i < n, 0 <= k-i < n
                for (int j = min(k , n - 1); j >= i; --j) {             // i <= j < n, 0 <= k-j < n
                    if (grid[i][k - i] == -1 ||
                        grid[j][k - j] == -1) {
                        dp[i][j] = -1;
                        continue;
                    }
                    int cnt = grid[i][k - i] + ((i == j) ? 0 : grid[j][k - j]);
                    int max_cnt = -1;
                    static const vector<pair<int, int>> directions{{0, 0}, {-1, 0}, {0, -1}, {-1, -1}};
                    for (const auto& direction : directions) {
                        const auto ii = i + direction.first;
                        const auto jj = j + direction.second;
                        if (ii >= 0 && jj >= 0 && dp[ii][jj] >= 0) {
                            max_cnt = max(max_cnt, dp[ii][jj] + cnt);
                        }
                    }
                    dp[i][j] = max_cnt;
                }
            }
        }
        return max(dp[n - 1][n - 1], 0);
    }

