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

    int maxHappyGroups(int batchSize, vector<int>& groups) {
        vector<int> count(batchSize);
        for (const auto& i : groups) {
            ++count[i % size(count)];
        }
        int result = count[0];
        count[0] = 0;
        for (int i = 1; i <= size(count) / 2; ++i) {
            int pair_count = 2 * i != size(count) ? min(count[i], count[size(count) - i]) : count[i] / 2;
            result += pair_count;
            count[i] -= pair_count;
            count[size(count) - i] -= pair_count;
        }
        unordered_map<int, int> new_count;
        for (int i = 0; i < size(count); ++i) {
            if (count[i]) {
                new_count[i] = count[i];
            }
        }
        int max_mask = accumulate(cbegin(new_count), cend(new_count), 1,
                                  [](int total, pair<int, int> kvp) {
                                      return total * (kvp.second + 1);
                                  });
        vector<int> dp(max_mask);
        for (int mask = 0; mask < size(dp); ++mask) {
            int remain = 0;
            int curr = mask, basis = 1;
                for (const auto& [i, c] : new_count) {
                // mask: a0 + a1 * (c0 + 1)  + a2 * (c0 + 1) * (c1 + 1) + ... + a(b-1) * (c0 + 1) * (c1 + 1) * ... * (c(b-2) + 1)
                int ai = curr % (count[i] + 1);
                if (ai > 0) {
                    dp[mask] = max(dp[mask], dp[mask - basis]);
                }
                remain = (remain + ai * i) % batchSize;
                basis *= (c + 1), curr /= (c + 1);
            }
            if (mask != size(dp) - 1 && remain == 0) {
                ++dp[mask];
            }
        }
        return result + dp.back();
    }

