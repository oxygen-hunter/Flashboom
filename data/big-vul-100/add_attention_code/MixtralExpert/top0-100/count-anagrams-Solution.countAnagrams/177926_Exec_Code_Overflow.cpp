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


    int countAnagrams(string s) {
        static const uint32_t MOD = 1e9 + 7;
        vector<int> fact = {1, 1};
        vector<int> inv = {1, 1};
        vector<int> inv_fact = {1, 1};
        const auto& lazy_init = [&](int n) {
            while (size(inv) <= n) {  // lazy initialization
                fact.emplace_back((static_cast<int64_t>(fact.back()) * size(inv)) % MOD);
                inv.emplace_back((static_cast<int64_t>(inv[MOD % size(inv)]) * (MOD - MOD / size(inv))) % MOD);  // https://cp-algorithms.com/algebra/module-inverse.html
                inv_fact.emplace_back((static_cast<int64_t>(inv_fact.back()) * inv.back()) % MOD);
            }
        };

        const auto& factorial = [&](int n) {
            lazy_init(n);
            return fact[n];
        };

        const auto& inv_factorial = [&](int n) {
            lazy_init(n);
            return inv_fact[n];
        };

        const auto& count = [&](int j, int i) {
            vector<int> cnt(26);
            for (int k = j; k <= i; ++k) {
                ++cnt[s[k] - 'a'];
            }
            int64_t result = 1;
            int total = 0;
            for (const auto& c : cnt) {
                total += c;
                result = (result * inv_factorial(c)) % MOD;
            }
            return (result * factorial(total)) % MOD;
        };

        int result = 1;
        for (int i = 0, j = 0; i < size(s); ++i) {
            if (i + 1 != size(s) && s[i + 1] != ' ') {
                continue;
            }
            result = (result * count(j, i)) % MOD;
            j = i + 2;
        }
        return result;
    }


