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


    int shortestSubarray(vector<int>& A, int K) {
        vector<int> accumulated_sum(A.size() + 1, 0);
        partial_sum(A.cbegin(), A.cend(), next(accumulated_sum.begin()), plus<int>());
        
        int result = numeric_limits<int>::max();
        deque<int> mono_increasing_q;
        for (int i = 0; i < accumulated_sum.size(); ++i) {
            while (!mono_increasing_q.empty() &&
                   accumulated_sum[i] <= accumulated_sum[mono_increasing_q.back()]) {
                mono_increasing_q.pop_back();
            }
            while (!mono_increasing_q.empty() &&
                   accumulated_sum[i] - accumulated_sum[mono_increasing_q.front()] >= K) {
                result = min(result, i - mono_increasing_q.front());
                mono_increasing_q.pop_front();
            }
            mono_increasing_q.emplace_back(i);
        }
        return result != numeric_limits<int>::max() ? result : -1;
    }


