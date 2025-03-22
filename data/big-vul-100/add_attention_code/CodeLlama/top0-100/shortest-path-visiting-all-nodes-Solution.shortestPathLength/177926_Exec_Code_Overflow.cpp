gst_vorbis_tag_add_coverart (GstTagList * tags, const gchar * img_data_base64,
     gint base64_len)
 {
   GstBuffer *img;
  guchar *img_data;
   gsize img_len;
   guint save = 0;
   gint state = 0;
 
   if (base64_len < 2)
     goto not_enough_data;
 
  img_data = g_try_malloc0 (base64_len * 3 / 4);
  if (img_data == NULL)
    goto alloc_failed;
  img_len = g_base64_decode_step (img_data_base64, base64_len, img_data,
      &state, &save);
 
   if (img_len == 0)
     goto decode_failed;
 
  img = gst_tag_image_data_to_image_buffer (img_data, img_len,
       GST_TAG_IMAGE_TYPE_NONE);
 
   if (img == NULL)
  gst_tag_list_add (tags, GST_TAG_MERGE_APPEND,
      GST_TAG_PREVIEW_IMAGE, img, NULL);

       GST_TAG_PREVIEW_IMAGE, img, NULL);
 
   gst_buffer_unref (img);
  g_free (img_data);
   return;
 
 /* ERRORS */
  {
    GST_WARNING ("COVERART tag with too little base64-encoded data");
     GST_WARNING ("COVERART tag with too little base64-encoded data");
     return;
   }
alloc_failed:
  {
    GST_WARNING ("Couldn't allocate enough memory to decode COVERART tag");
    return;
  }
 decode_failed:
   {
    GST_WARNING ("Couldn't decode bas64 image data from COVERART tag");
    g_free (img_data);
     return;
   }
 convert_failed:
   {
     GST_WARNING ("Couldn't extract image or image type from COVERART tag");
    g_free (img_data);
     return;
   }
 }


    int shortestPathLength(vector<vector<int>>& graph) {
        static const auto& INF = numeric_limits<int>::max();
        vector<vector<int>> dp(1 << graph.size(),
                               vector<int>(graph.size(), INF));
        queue<pair<int, int>> q;
        for (int i = 0; i < graph.size(); ++i) {
            dp[1 << i][i] = 0;
            q.emplace(1 << i, i);
        }
        while (!q.empty()) {
            int state, node;
            tie(state, node) = q.front(); q.pop();
            auto steps = dp[state][node];
            for (const auto& nei : graph[node]) {
                auto new_state = state | (1 << nei);								
                if (dp[new_state][nei] == INF) {
                    dp[new_state][nei] = steps + 1;
                    q.emplace(new_state, nei);
                }
            }
        }
        return *min_element(dp.back().cbegin(), dp.back().cend());
    }


