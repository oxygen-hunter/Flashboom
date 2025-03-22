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

    int maximalSquare(vector<vector<char>>& A) {
        if (A.empty()) {
            return 0;
        }

        // DP table stores (h, w) for each (i, j).
        vector<vector<MaxHW>> table(A.size(), vector<MaxHW>(A.front().size()));
        for (int i = A.size() - 1; i >= 0; --i) {
            for (int j = A[i].size() - 1; j >= 0; --j) {
                // Find the largest h such that (i, j) to (i + h - 1, j) are feasible.
                // Find the largest w such that (i, j) to (i, j + w - 1) are feasible.
                table[i][j] = A[i][j] == '1'
                                  ? MaxHW{i + 1 < A.size() ? table[i + 1][j].h + 1 : 1,
                                          j + 1 < A[i].size() ? table[i][j + 1].w + 1 : 1}
                                  : MaxHW{0, 0};
            }
        }

        // A table stores the length of largest square for each (i, j).
        vector<vector<int>> s(A.size(), vector<int>(A.front().size(), 0));
        int max_square_area = 0;
        for (int i = A.size() - 1; i >= 0; --i) {
            for (int j = A[i].size() - 1; j >= 0; --j) {
                int side = min(table[i][j].h, table[i][j].w);
                if (A[i][j]) {
                    // Get the length of largest square with bottom-left corner (i, j).
                    if (i + 1 < A.size() && j + 1 < A[i + 1].size()) {
                        side = min(s[i + 1][j + 1] + 1, side);
                    }
                    s[i][j] = side;
                    max_square_area = max(max_square_area, side * side);
                }
            }
        }
        return max_square_area;
    }

