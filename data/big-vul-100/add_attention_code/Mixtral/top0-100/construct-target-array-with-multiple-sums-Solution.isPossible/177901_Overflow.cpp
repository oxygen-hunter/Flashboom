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

    bool isPossible(vector<int>& target) {
        // (1) x + remain = y
        // (2) y + remain = total
        // (1) - (2) => x - y = y - total
        //           => x = 2*y - total
        auto total = accumulate(cbegin(target), cend(target), 0ll);
        priority_queue<int> max_heap(cbegin(target), cend(target));
        while (total != target.size()) {
            const auto y = max_heap.top(); max_heap.pop();
            const auto& remain = total - y;
            auto x = y - remain;
            if (x <= 0) {
                return false;
            }
            if (x > remain) {  // for case [1, 1000000000]
                x = x % remain + remain;
            }
            max_heap.emplace(x);
            total = x + remain;
        }
        return true;
    }

