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

    int maxProfit(int k, vector<int> &prices) {
        vector<int> profits;
        vector<pair<int, int>> v_p_stk;  // mono stack, where v is increasing and p is strictly decreasing
        for (int v = -1, p = -1; p + 1 < size(prices);) { // at most O(n) peaks, so v_p_stk and profits are both at most O(n) space
            for (v = p + 1; v + 1 < size(prices); ++v) {
                if (prices[v] < prices[v + 1]) {
                    break;
                }
            }
            for (p = v; p + 1 < size(prices); ++p) {
                if (prices[p] > prices[p + 1]) {
                    break;
                }
            }
            while (!empty(v_p_stk) && (prices[v_p_stk.back().first] > prices[v])) {  // not overlapped
                const auto [last_v, last_p] = move(v_p_stk.back()); v_p_stk.pop_back();
                profits.emplace_back(prices[last_p] - prices[last_v]);  // count [prices[last_v], prices[last_p]] interval
            }
            while (!empty(v_p_stk) && (prices[v_p_stk.back().second] <= prices[p])) {  // overlapped
                // prices[last_v] <= prices[v] <= prices[last_p] <= prices[p],
                // treat overlapped as [prices[v], prices[last_p]], [prices[last_v], prices[p]] intervals due to invariant max profit
                const auto [last_v, last_p] = move(v_p_stk.back()); v_p_stk.pop_back();
                profits.emplace_back(prices[last_p] - prices[v]);  // count [prices[v], prices[last_p]] interval
                v = last_v;  
            }
            v_p_stk.emplace_back(v, p);  // keep [prices[last_v], prices[p]] interval to check overlapped
        }        
        while (!empty(v_p_stk))  {
            const auto [last_v, last_p] = move(v_p_stk.back()); v_p_stk.pop_back();
            profits.emplace_back(prices[last_p] - prices[last_v]);  // count [prices[last_v], prices[last_p]] interval
        }
        if (k > size(profits)) {
            k = size(profits);
        } else {
            nth_element(begin(profits), begin(profits) + k - 1, end(profits), greater<int>());
        }
        return accumulate(cbegin(profits), cbegin(profits) + k, 0);  // top k profits of nonoverlapped intervals
    }

