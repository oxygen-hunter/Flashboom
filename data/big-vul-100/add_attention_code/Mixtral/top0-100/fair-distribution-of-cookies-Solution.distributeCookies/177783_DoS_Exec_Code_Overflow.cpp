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

    int distributeCookies(vector<int>& cookies, int k) {
        vector<int> total(1 << size(cookies));
        for (int mask = 0; mask < (1 << size(cookies)); ++mask) {
            for (int i = 0; i < size(cookies); ++i) {
                if (mask & (1 << i)) {
                    total[mask] += cookies[i];
                }
            }
        }
        vector<vector<int>> dp(2, vector<int>(1 << size(cookies), numeric_limits<int>::max()));
        dp[0][0] = 0;
        for (int i = 0; i < k; ++i) {
            for (int mask = 0; mask < (1 << size(cookies)); ++mask) {
                for (int submask = mask; submask; submask = (submask - 1) & mask) {
                    dp[(i + 1) % 2][mask] = min(dp[(i + 1) % 2][mask], max(total[submask], dp[i % 2][mask ^ submask]));
                }
            }
        }
        return dp[k % 2].back();
    }   

