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


    int minSwapsCouples(vector<int>& row) {
        int N = row.size() / 2;
        vector<vector<int>> couples(N);
        for (int seat = 0; seat < row.size(); ++seat) {
            couples[row[seat] / 2].emplace_back(seat / 2);
        }
        vector<vector<int>> adj(N);
        for (const auto& couple : couples) {
            adj[couple[0]].emplace_back(couple[1]);
            adj[couple[1]].emplace_back(couple[0]);
        }
        
        int result = 0;
        for (int couch = 0; couch < N; ++couch) {
            if (adj[couch].empty()) {
                continue;
            }
            int couch1 = couch;
            int couch2 = adj[couch1].back(); adj[couch1].pop_back();
            while (couch2 != couch) {
                ++result;
                adj[couch2].erase(find(adj[couch2].begin(), adj[couch2].end(), couch1));
                couch1 = couch2;
                couch2 = adj[couch1].back(); adj[couch1].pop_back();
            }
        }
        return result;  // also equals to N - (# of cycles)
    }


