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

    string minimizeError(vector<string>& prices, int target) {
        vector<double> errors;
        int lower = 0, upper = 0;
        for (const auto& price : prices) {
            const auto& p = stod(price);
            lower += floor(p);
            upper += ceil(p);
            if (p != floor(p)) {
                errors.emplace_back(p - floor(p));
            }
        }
        if (target < lower || target > upper) {
            return "-1";
        }

        int lower_round_count = upper - target;
        nth_element(errors.begin(), errors.begin() + lower_round_count, errors.end());
        double min_error = 0.0;
        for (int i = 0; i < errors.size(); ++i) {
            if (i < lower_round_count) {
                min_error += errors[i];
            } else {
                min_error += 1.0 - errors[i];
            }
        }
        const auto& result = to_string(min_error);
        return result.substr(0, result.find(".") + 4);
    }

