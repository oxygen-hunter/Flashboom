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


    int orangesRotting(vector<vector<int>>& grid) {
        static const vector<pair<int, int>> directions{{0, 1}, {1, 0},
                                                       {0, -1}, {-1, 0}};

        int count = 0;
        queue<tuple<int, int, int>> q;
        for (int r = 0; r < grid.size(); ++r) {
            for (int c = 0; c < grid[r].size(); ++c) {
                if (grid[r][c] == 2) {
                    q.emplace(r, c, 0);
                } else if (grid[r][c]  == 1) {
                    ++count;
                }
            }
        }

        int result = 0;
        while (!q.empty()) {
            int r, c;
            tie(r, c, result) = q.front(); q.pop();
            for (const auto& d : directions) {
                int nr = r + d.first, nc = c + d.second;
                if  (!(0 <= nr && nr < grid.size() &&
                       0 <= nc && nc < grid[r].size())) {
                    continue;
                }
                if (grid[nr][nc] == 1) {
                    --count;
                    grid[nr][nc] = 2;
                    q.emplace(nr, nc, result + 1);
                }
            }
        }
        return (count == 0) ? result : -1;
    }


