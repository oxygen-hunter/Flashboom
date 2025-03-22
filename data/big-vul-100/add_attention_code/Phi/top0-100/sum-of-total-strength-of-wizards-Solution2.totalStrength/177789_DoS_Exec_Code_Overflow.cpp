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

    int totalStrength(vector<int>& strength) {
        static const int MOD = 1e9 + 7;
        const auto& add = [&](const int64_t a, const int64_t b) {
            return (a + b) % MOD;
        };
        const auto& sub = [&](const int64_t a, const int64_t b) {
            return (a - b + MOD) % MOD;
        };
        const auto& mult = [&](const int64_t a, const int64_t b) {
            return (a * b) % MOD;
        };
        vector<int64_t> prefix(size(strength) + 1), prefix2(size(strength) + 1);
        for (int i = 0; i < size(strength); ++i) {
            prefix[i + 1] = add(prefix[i], strength[i]);
            prefix2[i + 1] = add(prefix2[i], strength[i] * static_cast<int64_t>(i + 1));
        }
        vector<int64_t> suffix(size(strength) + 1), suffix2(size(strength) + 1);
        for (int i = size(strength) - 1; i >= 0; --i) {
            suffix[i] = add(suffix[i + 1], strength[i]);
            suffix2[i] = add(suffix2[i + 1], strength[i] * (size(strength) - i));
        }
        vector<int> stk = {-1};
        int result = 0;
        for (int i = 0; i <= size(strength); ++i) {
            while (stk.back() != -1 && (i == size(strength) || strength[stk.back()] >= strength[i])) {
                const int x = stk[size(stk) - 2] + 1;
                const int y = stk.back(); stk.pop_back();
                const int z = i - 1;
                // assert(all(strength[j] >= strength[y] for j in xrange(x, y+1)))
                // assert(all(strength[j] > strength[y] for j in xrange(y+1, z+1)))
                const int64_t left = mult(z - y + 1, sub(sub(prefix2[y + 1], prefix2[x]), mult(x, sub(prefix[y + 1], prefix[x]))));
                const int64_t right = mult(y - x + 1, sub(sub(suffix2[y + 1], suffix2[z + 1]), mult(size(strength) - (z + 1), sub(suffix[y + 1], suffix[z + 1]))));
                result = add(result, mult(strength[y], add(left, right)));
            }
            stk.emplace_back(i);
        }
        return result;
    }

