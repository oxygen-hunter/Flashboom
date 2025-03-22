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


    int shortestPathWithHops(int n, vector<vector<int>>& edges, int s, int d, int k) {
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].emplace_back(e[1], e[2]);
            adj[e[1]].emplace_back(e[0], e[2]);
        }
        const auto& modified_dijkstra = [&]() {
            static const int INF = numeric_limits<int>::max();

            vector<vector<int>> best(size(adj), vector<int>(k + 1, INF));
            best[s][0] = 0;
            priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> min_heap;
            min_heap.emplace(best[s][0], s, 0);
            while (!empty(min_heap)) {
                const auto [curr, u, cnt] = min_heap.top(); min_heap.pop();
                if (curr > best[u][cnt]) {
                    continue;
                }
                if (u == d) {
                    return curr;
                }
                for (const auto& [v, w] : adj[u]) {
                    if (w < best[v][cnt] - curr) {
                        best[v][cnt] = curr + w;
                        min_heap.emplace(best[v][cnt], v, cnt);
                    }
                    if (cnt + 1 <= k && curr < best[v][cnt + 1]) {
                        best[v][cnt + 1] = curr;
                        min_heap.emplace(best[v][cnt + 1], v, cnt + 1);
                    }
                }
            }
            return -1;
        };

        return modified_dijkstra();
    }


