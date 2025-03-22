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

    int ways(vector<string>& pizza, int k) {
        static int MOD = 1e9 + 7;
        vector<vector<int>> prefix(pizza.size(), vector<int>(pizza[0].size()));
        for (int j = pizza[0].size() - 1; j >= 0; --j) {
            for (int accu = 0, i = pizza.size() - 1; i >= 0; --i) {
                accu += pizza[i][j] == 'A';
                prefix[i][j] = ((j + 1 != pizza[0].size()) ? prefix[i][j + 1] : 0) + accu;
            }
        }
        vector<vector<vector<uint64_t>>> dp(pizza.size(),
                                            vector<vector<uint64_t>>(pizza[0].size(),
                                            vector<uint64_t>(k)));
        for (int i = pizza.size() - 1; i >= 0; --i) {
            for (int j = pizza[0].size() - 1; j >= 0; --j) {
                dp[i][j][0] = 1;
                for (int m = 1; m < k; ++m) {
                    for (int n = i + 1; n < pizza.size() && prefix[n][j]; ++n) {
                        if (prefix[i][j] == prefix[n][j]) {
                            continue;
                        }
                        dp[i][j][m] = (dp[i][j][m] + dp[n][j][m - 1]) % MOD;
                    }
                    for (int n = j + 1; n < pizza[0].size() && prefix[i][n]; ++n) {
                        if (prefix[i][j] == prefix[i][n]) {
                            continue;
                        }
                        dp[i][j][m] = (dp[i][j][m] + dp[i][n][m - 1]) % MOD;
                    }
                }
            }
        }
        return dp[0][0][k - 1];
    }

