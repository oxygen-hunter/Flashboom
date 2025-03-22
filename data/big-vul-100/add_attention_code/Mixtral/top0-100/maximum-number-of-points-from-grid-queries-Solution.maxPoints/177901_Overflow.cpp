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

    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        static const vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> min_heap;
        min_heap.emplace(grid[0][0], 0, 0);
        vector<vector<bool>> lookup(size(grid), vector<bool>(size(grid[0])));
        lookup[0][0] = true;
        unordered_map<int, int> cnt;
        int mx = 0;
        while (!empty(min_heap)) {
            const auto [curr, i, j] = min_heap.top(); min_heap.pop();
            mx = max(mx, curr);
            ++cnt[mx];
            for (const auto& [di, dj] : directions) {
                const int ni = i + di, nj = j + dj;
                if (!(0 <= ni && ni < size(grid) &&
                      0 <= nj && nj < size(grid[0]) &&
                      !lookup[ni][nj])) {
                    continue;
                }
                lookup[ni][nj] = true;
                min_heap.emplace(grid[ni][nj], ni, nj);
            }
        }
        vector<int> vals;
        for (const auto& [k, _] : cnt) {
            vals.emplace_back(k);
        }
        sort(begin(vals), end(vals));
        vector<int> prefix(size(vals) + 1);
        for (int i = 0; i < size(vals); ++i) {
            prefix[i + 1] = prefix[i] + cnt[vals[i]];
        }
        vector<int> result(size(queries));
        for (int i = 0; i < size(queries); ++i) {
            result[i] = prefix[distance(cbegin(vals), lower_bound(cbegin(vals), cend(vals), queries[i]))];
        }
        return result;
    }

