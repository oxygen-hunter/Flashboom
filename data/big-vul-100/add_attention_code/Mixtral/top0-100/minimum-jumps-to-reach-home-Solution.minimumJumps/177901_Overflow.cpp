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

    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        int max_f = *max_element(cbegin(forbidden), cend(forbidden));
        int max_val = (a >= b) ? x + b : max(x, max_f) + a + b;  // a may be a non-periodic area, (a+b) is a periodic area which is divided by gcd(a, b) and all points are reachable
        vector<unordered_set<int>> lookup(2); 
        for (const auto& pos : forbidden) {
            lookup[0].emplace(pos);
            lookup[1].emplace(pos);
        }
        int result = 0;
        vector<pair<int, int>> q = {{0, true}};
        lookup[0].emplace(0);
        while (!empty(q)) {
            vector<pair<int, int>> new_q;
            for (const auto& [pos, can_back] : q) {
                if (pos == x) {
                    return result;
                }
                if (pos + a <= max_val && !lookup[0].count(pos + a)) {
                    lookup[0].emplace(pos + a);
                    new_q.emplace_back(pos + a, true);
                }
                if (!can_back) {
                    continue;
                }
                if (pos - b >= 0 && !lookup[1].count(pos - b)) {
                    lookup[1].emplace(pos - b);
                    new_q.emplace_back(pos - b, false);
                }
            }
            q = move(new_q);
            ++result;
        }
        return -1;
    }

