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

    int numberOfWays(int n, int m, int k, vector<int>& source, vector<int>& dest) {
        static const int MOD = 1e9 + 7;
    
        int both_same = 0, row_same = 0, col_same = 0, no_same = 0;
        if (source == dest) {
            both_same = 1;
        } else if (source[0] == dest[0]) {
            row_same = 1;
        } else if (source[1] == dest[1]) {
            col_same = 1;
        } else {
            no_same = 1;
        }
        for (int _ = 0; _ < k; ++_) {
            tie(both_same, row_same, col_same, no_same) = tuple(
                (row_same + col_same) % MOD,
                (both_same * static_cast<int64_t>(m - 1) + row_same * static_cast<int64_t>(m - 2) + no_same) % MOD,
                (both_same * static_cast<int64_t>(n - 1) + col_same * static_cast<int64_t>(n - 2) + no_same) % MOD,
                (row_same * static_cast<int64_t>(n - 1) + col_same * static_cast<int64_t>(m - 1) + no_same * static_cast<int64_t>((n - 2) + (m - 2))) % MOD
            );
        }
        return both_same;
    }

