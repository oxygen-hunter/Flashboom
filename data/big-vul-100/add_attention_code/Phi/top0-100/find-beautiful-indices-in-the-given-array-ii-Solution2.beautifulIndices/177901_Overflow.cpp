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

    vector<int> beautifulIndices(string s, string a, string b, int k) {
        const auto& KMP = [&](const string& text, const string& pattern) {
            const auto& getPrefix = [&](const string& pattern) {
                vector<int> prefix(pattern.length(), -1);
                int j = -1;
                for (int i = 1; i < pattern.length(); ++i) {
                    while (j > -1 && pattern[j + 1] != pattern[i]) {
                        j = prefix[j];
                    }
                    if (pattern[j + 1] == pattern[i]) {
                        ++j;
                    }
                    prefix[i] = j;
                }
                return prefix;
            };

            vector<int> result;
            const vector<int> prefix = getPrefix(pattern + '#' + text);
            for (int i = (size(pattern) + 1) + (size(pattern) - 1); i < size(prefix); ++i) {
                if (prefix[i] + 1 == size(pattern)) {
                    result.emplace_back((i - (size(pattern) + 1)) - (size(pattern) - 1));
                }
            }
            return result;
        };

        vector<int> result;
        if (!(size(a) <= size(s) && size(b) <= size(s))) {
            return result;
        }
        const auto& lookup = KMP(s, b);
        int j = 0;
        for (const auto& i : KMP(s, a)) {
            const int j = distance(cbegin(lookup), lower_bound(cbegin(lookup), cend(lookup), i - k));
            if (j < size(lookup) && lookup[j] <= i + k) {
                result.emplace_back(i);
            }
        }
        return result;
    }

