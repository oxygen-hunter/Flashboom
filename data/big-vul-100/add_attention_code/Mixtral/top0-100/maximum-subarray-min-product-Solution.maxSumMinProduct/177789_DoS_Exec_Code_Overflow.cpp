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

    int maxSumMinProduct(vector<int>& nums) {
        static const int MOD = 1e9 + 7;

        vector<int64_t> prefix(nums.size() + 1);
        for (int i = 0; i < size(nums); ++i) {
           prefix[i + 1] = prefix[i] + nums[i];
        }
        vector<int> stk = {-1};
        int64_t result = 0;
        for (int i = 0; i <= size(nums); ++i) {
            while (stk.back() != -1 && (i == size(nums) || nums[stk.back()] >= nums[i])) {
                int j = stk.back();
                stk.pop_back();
                result = max(result, nums[j] * (prefix[(i - 1) + 1] - prefix[stk.back() + 1]));
            }
            stk.emplace_back(i);
        }
        return result % MOD;
    }

