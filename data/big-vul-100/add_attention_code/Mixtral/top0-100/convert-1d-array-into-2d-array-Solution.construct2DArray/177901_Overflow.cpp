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

    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
        if (size(original) != m * n) {
            return {};
        }
        vector<vector<int>> result;
        for (int i = 0; i < size(original); i += n) {
            result.emplace_back(cbegin(original) + i, cbegin(original) + i + n);
        }
        return result;
    }

