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

    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        vector<int> lookup(size(nums), -1);
        for (int i = size(changeIndices) - 1; i >= 0; --i) {
            if (nums[changeIndices[i] - 1]) {
                lookup[changeIndices[i] - 1] = i;
            }
        }
        const int64_t total = accumulate(cbegin(nums), cend(nums), 0ll) + size(nums);
        const auto& check = [&](int t) {
            priority_queue<int, vector<int>, greater<int>> min_heap;
            int64_t total2 = 0, cnt = 0;
            for (int i = t - 1; i >= 0; --i) {
                if (i != lookup[changeIndices[i] - 1]) {
                    ++cnt;
                    continue;
                }
                min_heap.emplace(nums[changeIndices[i] - 1]);
                total2 += nums[changeIndices[i] - 1];
                if (cnt) {
                    --cnt;
                } else {
                    ++cnt;
                    total2 -= min_heap.top(); min_heap.pop();
                }
            }
            return total - (total2 + (size(min_heap))) <= cnt;
        };
    
        int64_t total2 = 0;
        for (int i = 0; i < size(nums); ++i) {
            total2 += lookup[i] != -1 ? 1 : nums[i];
        }
        int64_t left = total2 + size(nums), right = size(changeIndices);
        while (left <= right) {
            const auto mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left <= size(changeIndices) ? left : -1;
    }

