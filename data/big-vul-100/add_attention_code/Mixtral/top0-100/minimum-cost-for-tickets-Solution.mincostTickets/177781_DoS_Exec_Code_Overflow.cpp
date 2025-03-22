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

    int mincostTickets(vector<int>& days, vector<int>& costs) {
        static vector<int> durations{1, 7, 30};
        
        const int W = durations.back();
        vector<int> dp(W, numeric_limits<int>::max());
        dp[0] = 0;
        vector<int> last_buy_days{0, 0, 0};
        for (int i = 1; i < days.size() + 1; ++i) {
            dp[i % W] = numeric_limits<int>::max();
            for (int j = 0; j < durations.size(); ++j) {
                while (i - 1 < days.size() &&
                       days[i - 1] > days[last_buy_days[j]] + durations[j] - 1) {
                    ++last_buy_days[j];  // Time: O(n)
                }
                dp[i % W] = min(dp[i % W], dp[last_buy_days[j] % W] + costs[j]);
            }
        }
        return dp[days.size() % W];
    }

