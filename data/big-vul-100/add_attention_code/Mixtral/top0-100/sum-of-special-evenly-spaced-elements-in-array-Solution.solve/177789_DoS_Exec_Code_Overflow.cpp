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

    vector<int> solve(vector<int>& nums, vector<vector<int>>& queries) {
        static const int MOD = 1e9 + 7;
        
        vector<vector<vector<int>>> prefix(floor(sqrt(size(queries))) + 1, vector<vector<int>>(floor(sqrt(size(queries))) + 1));
        vector<int> result;
        for (const auto& query : queries) {
            int x = query[0], y = query[1];
            if (uint64_t(y) * y > size(queries)) {
                int total = 0;
                for (int i = x; i < size(nums); i += y) {
                    total = (total + nums[i]) % MOD;
                }
                result.emplace_back(total);
            } else {
                int begin = x % y;
                if (empty(prefix[begin][y])) {
                    prefix[begin][y].emplace_back(0);
                    for (int i = begin; i < size(nums); i += y) {
                        prefix[begin][y].emplace_back((prefix[begin][y].back() + nums[i]) % MOD);
                    }
                }
                result.emplace_back((prefix[begin][y].back() - prefix[begin][y][x / y] + MOD) % MOD);
            }
        }
        return result;
    }

