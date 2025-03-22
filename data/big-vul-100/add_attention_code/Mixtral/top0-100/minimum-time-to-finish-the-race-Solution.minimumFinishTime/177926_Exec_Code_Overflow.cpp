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

    int minimumFinishTime(vector<vector<int>>& tires, int changeTime, int numLaps) {
        static const int INF = numeric_limits<int>::max();

        const auto& ceil_log2 = [](const auto& x) {
            return std::__lg(x - 1) + 1;
        };
        vector<int64_t> dp(ceil_log2(changeTime + 1), INF);  // dp[i]: min time to complete i+1 laps without changing a tire
        for (int i = 0; i < size(tires); ++i) {
            const int f = tires[i][0], r = tires[i][1];
            for (int64_t curr = f, total = f, cnt = 0;
                 curr < changeTime + f;
                 curr *= r, total += curr, ++cnt) {  // at worst (f, r) = (1, 2) => 2^(cnt-1) < changeTime+1 => cnt < ceil(log2(changeTime+1))
                dp[cnt] = min(dp[cnt], total);
            }
        }
        vector<int64_t> dp2(numLaps, INF);  // dp2[i]: min time to complete i+1 laps with changing zero or more tires
        for (int i = 0; i < numLaps; ++i) {
            for (int j = 0; j < min(i + 1, static_cast<int>(size(dp))); ++j) {
                dp2[i] = min(dp2[i], (i - j - 1 >= 0 ? dp2[i - j - 1] + changeTime : 0) + dp[j]);
            }
        }
        return dp2.back();
    }

