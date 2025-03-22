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


    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<pair<int, int>> pairs;
        if (nums1.size() > nums2.size()) {
            vector<pair<int, int>> tmp = kSmallestPairs(nums2, nums1, k);
            for (const auto& pair : tmp) {
                pairs.emplace_back(pair.second, pair.first);
            }
            return pairs;
        }

        using P = pair<int, pair<int, int>>;
        priority_queue<P, vector<P>, greater<P>> q;
        auto push = [&nums1, &nums2, &q](int i, int j) {
            if (i < nums1.size() && j < nums2.size()) {
                q.emplace(nums1[i] + nums2[j], make_pair(i, j));
            }
        };

        push(0, 0);
        while (!q.empty() && pairs.size() < k) {
            auto tmp = q.top(); q.pop();
            int i, j;
            tie(i, j) = tmp.second;
            pairs.emplace_back(nums1[i], nums2[j]);
            push(i, j + 1);
            if (j == 0) {
                push(i + 1, 0);  // at most queue min(m, n) space.
            }
        }
        return pairs; 
    }


