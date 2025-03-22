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

    int largestVariance(string s) {
        const auto& modified_kadane = [&s](const auto& x, const auto& y) {
            int result = 0;
            vector<int> lookup(2);
            vector<int> remain = {static_cast<int>(count(cbegin(s), cend(s), x)),
                                  static_cast<int>(count(cbegin(s), cend(s), y))};
            int curr = 0;
            for (const auto& c : s) {
                if (!(c == x || c == y)) {
                    continue;
                }
                lookup[c != x] = 1;
                --remain[c != x];
                curr += (c == x) ? 1 : -1;
                if (curr < 0 && remain[0] && remain[1]) {
                    curr = lookup[0] = lookup[1] = 0;  // reset states if the remain has both x, y
                }
                if (lookup[0] && lookup[1]) {
                    result = max(result, curr);  // update result if x, y both exist
                }
            }
            return result;
        };
        
        unordered_set<char> alphabets(cbegin(s), cend(s));
        int result = 0;
        for (const auto& x : alphabets) {
            for (const auto& y: alphabets) {
                if (x != y) {
                    result = max(result, modified_kadane(x, y));
                }
            }
        }
        return result;
    }

