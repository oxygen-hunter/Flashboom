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

    string fractionToDecimal(int numerator, int denominator) {
        string result;
        if ((numerator ^ denominator) >> 31 && numerator != 0) {
            result = "-";
        }

        auto dvd = llabs(numerator);
        auto dvs = llabs(denominator);
        result += to_string(dvd / dvs);
        dvd %= dvs;
        if (dvd > 0) {
            result += ".";
        }
        
        unordered_map<long long, int> lookup;
        while (dvd && !lookup.count(dvd)) {
            lookup[dvd] = result.length();
            dvd *= 10;
            result += to_string(dvd / dvs);
            dvd %= dvs;
        }

        if (lookup.count(dvd)) {
            result.insert(lookup[dvd], "(");
            result.push_back(')');
        }
        return result;
    }

