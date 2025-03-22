void GfxImageColorMap::getGrayLine(Guchar *in, Guchar *out, int length) {
  int i, j;
  Guchar *inp, *tmp_line;

   switch (colorSpace->getMode()) {
   case csIndexed:
   case csSeparation:
    tmp_line = (Guchar *) gmalloc (length * nComps2);
     for (i = 0; i < length; i++) {
       for (j = 0; j < nComps2; j++) {
 	tmp_line[i * nComps2 + j] = byte_lookup[in[i] * nComps2 + j];
      }
    }
    colorSpace2->getGrayLine(tmp_line, out, length);
    gfree (tmp_line);
    break;

  default:
    inp = in;
    for (j = 0; j < length; j++)
      for (i = 0; i < nComps; i++) {
	*inp = byte_lookup[*inp * nComps + i];
	inp++;
      }
    colorSpace->getGrayLine(in, out, length);
    break;
  }

}


    vector<long long> countBlackBlocks(int m, int n, vector<vector<int>>& coordinates) {
        static const int L = 2;
    
        unordered_map<int64_t, int> cnt;
        for (const auto& c : coordinates) {
            const int x = c[0], y = c[1];
            for (int nx = max(x - (L - 1), 0); nx < min(x + 1, m - (L - 1)); ++nx) {
                for (int ny = max(y - (L - 1), 0); ny < min(y + 1, n - (L - 1)); ++ny) {
                    ++cnt[static_cast<int64_t>(nx) * n + ny];
                }
            }
        }
        vector<long long> result(L * L + 1);
        for (const auto& [_, c] : cnt) {
            ++result[c];
        }
        result[0] = static_cast<int64_t>(m - (L - 1)) * (n - (L - 1)) - accumulate(cbegin(result) + 1, cend(result), 0ll);
        return result;
    }


