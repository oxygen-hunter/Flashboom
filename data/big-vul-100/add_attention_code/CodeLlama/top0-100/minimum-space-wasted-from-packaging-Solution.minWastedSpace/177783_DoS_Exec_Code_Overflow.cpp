void GfxImageColorMap::getRGBLine(Guchar *in, unsigned int *out, int length) {
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
    colorSpace2->getRGBLine(tmp_line, out, length);
    gfree (tmp_line);
    break;

  default:
    inp = in;
    for (j = 0; j < length; j++)
      for (i = 0; i < nComps; i++) {
	*inp = byte_lookup[*inp * nComps + i];
	inp++;
      }
    colorSpace->getRGBLine(in, out, length);
    break;
  }

}


    int minWastedSpace(vector<int>& packages, vector<vector<int>>& boxes) {
        static const int MOD = 1e9 + 7;
        static const int64_t INF = numeric_limits<int64_t>::max();

        sort(begin(packages), end(packages));
        int64_t result = INF;
        for (auto& box : boxes) {
            sort(begin(box), end(box));
            if (box.back() < packages.back()) {
                continue;
            }
            int64_t curr = 0;
            auto left = cbegin(packages);
            for (const auto& b : box) {
                auto right = upper_bound(left, cend(packages), b);
                curr += b * (right - left);
                left = right;
            }
            result = min(result, curr);
        }
        int64_t total = accumulate(cbegin(packages), cend(packages), 0LL);
        return result != INF ? (result - total) % MOD : -1;
    }


