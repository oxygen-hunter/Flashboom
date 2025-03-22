_asn1_ltostr (long v, char *str)
 {
   long d, r;
   char temp[LTOSTR_MAX_SIZE];
  int count, k, start;

  if (v < 0)
    {
      str[0] = '-';
      start = 1;
      v = -v;
    }
  else
    start = 0;

  count = 0;
  do
    {
      d = v / 10;
      r = v - d * 10;
      temp[start + count] = '0' + (char) r;
       count++;
       v = d;
     }
  while (v);
 
   for (k = 0; k < count; k++)
     str[k + start] = temp[start + count - k - 1];
  str[count + start] = 0;
  return str;
}


    int countPairs(vector<int>& deliciousness) {
        static const int MOD = 1e9 + 7;

        static const auto& floor_log2_x = [](int x) {
            return 8 * sizeof(int) - __builtin_clz(x) - 1;
        };
        
        int max_pow = floor_log2_x(*max_element(cbegin(deliciousness),
                                                cend(deliciousness))) + 1;
        unordered_map<int, int> cnt;
        int result = 0;
        for (const auto& d : deliciousness) {
            int p = 1;
            for (int i = 0; i <= max_pow; ++i) {
                result = (result + cnt[p - d]) % MOD;
                p <<= 1;
            }
            ++cnt[d];
        }
        return result;
    }


