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

    int seat() {
        while (!seats_.count(max_heap_.top().first) ||
               !seats_.count(max_heap_.top().second) ||
               seats_[max_heap_.top().first].second != max_heap_.top().second ||
               seats_[max_heap_.top().second].first != max_heap_.top().first) {
            max_heap_.pop();  // lazy deletion
        }
        
        const auto top = max_heap_.top(); max_heap_.pop();
        const auto& mid = top.first == -1 ? 0
                          : top.second == num_ ? num_ - 1
                          : (top.first + top.second) / 2;
        seats_[mid] = top;
        seats_[top.first].second = mid;
        seats_[top.second].first = mid;
        max_heap_.emplace(top.first, mid);
        max_heap_.emplace(mid, top.second);
        return mid;
    }

