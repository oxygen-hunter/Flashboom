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


    int smallestRepunitDivByK(int K) {
        // by observation, K % 2 = 0 or K % 5 = 0, it is impossible
        if (K % 2 == 0 || K % 5 == 0) {
            return -1;
        }
        // let f(N) is a N-length integer only containing digit 1
        // given K % 2 != 0 and K % 5 != 0
        // if there is no N in range (1..K) s.t. f(N) % K = 0
        // => there must be K remainders of f(N) % K in range (1..K-1) excluding 0
        // => due to pigeonhole principle, there must be at least 2 same remainders
        // => there must be some x, y in range (1..K) and x > y s.t. f(x) % K = f(y) % K
        // => (f(x) - f(y)) % K = 0
        // => (f(x-y) * 10^y) % K = 0
        // => due to (x-y) in range (1..K)
        // => f(x-y) % K != 0
        // => 10^y % K = 0
        // => K % 2 = 0 or K % 5 = 0
        // => -><-
        // it proves that there must be some N in range (1..K) s.t. f(N) % K = 0
        int result = 0;
        for (int N = 1; N <= K; ++N) {
            result = (result * 10 + 1) % K;
            if (!result) {
                return N;
            }
        }
        assert(false);
        return -1;  // never reach
    }


