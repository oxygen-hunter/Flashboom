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


        string convert(string s, int nRows) {
            vector<string> row(nRows);
            string ans;
            int cnt = 0;

            if(nRows == 1)
                return s;

            for(auto c : s) {
                if(cnt < nRows) {
                    row[cnt].push_back(c);
                }
                else {
                    row[2 * nRows - 2 - cnt].push_back(c);
                }

                cnt = (cnt + 1) % (2 * nRows - 2);
            }

            for(auto s : row) {
                ans.append(s);
            }

            return ans;
        }


