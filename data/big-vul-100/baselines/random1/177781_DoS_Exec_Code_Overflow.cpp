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


    int countTriplets(vector<int>& arr) {
        unordered_map<int, pair<int, int>> count_sum;
        count_sum[0] = {1, 0};
        int result = 0;
        for (int i = 0, prefix = 0; i < arr.size(); ++i) {
            prefix ^= arr[i];
            auto& [c, t] = count_sum[prefix];
            result += c * i - t;
            ++c, t += i + 1;
        }
        return result;
    }


