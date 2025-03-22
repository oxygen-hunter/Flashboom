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

    string oddString(vector<string>& words) {
        for (int i = 0; i < size(words[0]) - 1; ++i) {
            unordered_map<int, vector<int>> lookup;
            for (int j = 0; j < size(words); ++j) {
                if (size(lookup[words[j][i + 1] - words[j][i]]) < 2) {
                    lookup[words[j][i + 1] - words[j][i]].emplace_back(j);
                }
            }
            if (size(lookup) == 2) {
                return size(cbegin(lookup)->second) == 1
                       ? words[cbegin(lookup)->second[0]]
                       : words[next(cbegin(lookup))->second[0]];
            }
        }
        return "";
    }

