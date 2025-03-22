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


    int maxScore(vector<int>& nums) {
        vector<int> dp(1 << size(nums));
        for (int mask = 3; mask < size(dp); ++mask) {
            int cnt = __builtin_popcount(mask);
            if (cnt % 2) {
                continue;
            }
            vector<int> bits;
            for (int i = 0, m = mask; m; ++i, m >>= 1) {
                if (m & 1) {
                    bits.emplace_back(i);
                }
            }
            for (int i = 0; i < size(bits); ++i) {
                for (int j = i + 1; j < size(bits); ++j) {
                    dp[mask] = max(dp[mask], cnt / 2 * gcd(nums[bits[i]], nums[bits[j]]) + dp[mask ^ (1 << bits[i]) ^ (1 << bits[j])]);
                }
            }
        }
        return dp.back();
    }


