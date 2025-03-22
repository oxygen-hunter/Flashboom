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

    int minOperations(vector<int>& nums) {
        static const int INF = numeric_limits<int>::max();

        const int cnt = count(cbegin(nums), cend(nums), 1);
        if (cnt) {
            return size(nums) - cnt;
        }
        int result = INF;
        for (int i = 0; i < size(nums); ++i) {
            int g = nums[i];
            for (int j = i + 1; j < size(nums); ++j) {
                g = gcd(g, nums[j]);
                if (g == 1) {
                    result = min(result, j - i);
                    break;
                }
            }
        }
        return result != INF ? result + (size(nums) - 1) : -1;
    }

