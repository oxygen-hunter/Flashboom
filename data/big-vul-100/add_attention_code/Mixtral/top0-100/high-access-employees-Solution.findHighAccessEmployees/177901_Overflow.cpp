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

    vector<string> findHighAccessEmployees(vector<vector<string>>& access_times) {
        static const int LIMIT_COUNT = 2;
        static const int LIMIT_MINUTE = 60;
    
        const auto& to_minute = [](const auto& s) {
            return stoi(s.substr(0, 2)) * 60 + stoi(s.substr(2));
        };
    
        unordered_map<string, vector<int>> lookup;;
        for (const auto& x : access_times) {
            lookup[x[0]].emplace_back(to_minute(x[1]));
        }
        vector<string> result;
        for (auto& [x, ts] : lookup) {
            sort(begin(ts), end(ts));
            for (int i = 0; i + LIMIT_COUNT < size(ts); ++i) {
                if (!(ts[i] + LIMIT_MINUTE <= ts[i + LIMIT_COUNT])) {
                    result.emplace_back(x);
                    break;
                }
            } 
        }
        return result;
    }

