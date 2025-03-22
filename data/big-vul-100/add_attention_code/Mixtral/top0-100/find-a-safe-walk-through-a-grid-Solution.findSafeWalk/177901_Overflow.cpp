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

    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        static const vector<pair<int, int>> directions = {{0, 1}, {0, -1},
                                                          {1, 0}, {-1, 0}};
        const pair<int, int> b = {0, 0}, t = {size(grid) - 1, size(grid[0]) - 1};
        if (!(0 + grid[0][0] < health)) {
            return false;
        }
        deque<pair<pair<int, int>, int>> dq = {{b, grid[0][0]}};
        unordered_set<int> lookup;
        while (!empty(dq)) {
            const auto [b, d] = dq.front(); dq.pop_front();
            if (b == t) {
                return true;
            }
            if (lookup.count(b.first * size(grid[0]) + b.second)) {
                continue;
            }
            lookup.emplace(b.first * size(grid[0]) + b.second);
            for (const auto& [dr, dc] : directions) {
                const auto& nb = make_pair(b.first + dr, b.second + dc);
                if (!(0 <= nb.first && nb.first < size(grid) &&
                      0 <= nb.second && nb.second < size(grid[0]) &&
                      !lookup.count(nb.first * size(grid[0]) + nb.second))) {
                    continue;
                }
                if (!grid[nb.first][nb.second]) {
                    dq.emplace_front(nb, d);
                } else if (d + 1 < health) {
                    dq.emplace_back(nb, d + 1);
                }
            }
        }
        return false;
    }

