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


    vector<int> solve(vector<int>& nums, vector<vector<int>>& queries) {
        static const int MOD = 1e9 + 7;
        
        vector<vector<vector<int>>> prefix(floor(sqrt(size(queries))) + 1, vector<vector<int>>(floor(sqrt(size(queries))) + 1));
        vector<int> result;
        for (const auto& query : queries) {
            int x = query[0], y = query[1];
            if (uint64_t(y) * y > size(queries)) {
                int total = 0;
                for (int i = x; i < size(nums); i += y) {
                    total = (total + nums[i]) % MOD;
                }
                result.emplace_back(total);
            } else {
                int begin = x % y;
                if (empty(prefix[begin][y])) {
                    prefix[begin][y].emplace_back(0);
                    for (int i = begin; i < size(nums); i += y) {
                        prefix[begin][y].emplace_back((prefix[begin][y].back() + nums[i]) % MOD);
                    }
                }
                result.emplace_back((prefix[begin][y].back() - prefix[begin][y][x / y] + MOD) % MOD);
            }
        }
        return result;
    }


