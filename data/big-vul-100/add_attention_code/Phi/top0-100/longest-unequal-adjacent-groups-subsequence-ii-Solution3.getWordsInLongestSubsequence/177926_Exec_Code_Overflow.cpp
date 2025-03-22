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

    vector<string> getWordsInLongestSubsequence(int n, vector<string>& words, vector<int>& groups) {
        const auto& check = [&](const auto& s1, const auto& s2) {
            if (size(s1) != size(s2)) {
                return false;
            }
            int cnt = 0;
            for (int k = 0; k < size(s1); ++k) {
                cnt += s1[k] != s2[k] ? 1 : 0;
                if (cnt == 2) {
                    return false;
                }
            }
            return cnt == 1;
        };

        vector<vector<int>> dp(n);
        for (int i = 0; i < n; ++i) {
            const auto& si = words[i];
            int mx_j = -1;
            for (int j = 0; j < i; ++j) {
                if (groups[i] != groups[j] && check(words[j], si) && (mx_j == -1 || size(dp[mx_j]) < size(dp[j]))) {
                    mx_j = j;
                }
            }
            if (mx_j != -1) {
                dp[i] = dp[mx_j];
            }
            dp[i].emplace_back(i);
        }
        
        const auto& ans = *max_element(cbegin(dp), cend(dp), [](const auto& a, const auto& b) {
            return size(a) < size(b);
        });
        vector<string> result;
        for (const auto& i : ans) {
            result.emplace_back(words[i]);
        }
        return result;
    }

