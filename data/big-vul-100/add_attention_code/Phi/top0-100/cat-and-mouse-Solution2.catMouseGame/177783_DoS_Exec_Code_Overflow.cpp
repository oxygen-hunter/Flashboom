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

    int catMouseGame(vector<vector<int>>& graph) {
        vector<vector<vector<int>>> degree(size(graph), vector<vector<int>>(size(graph), vector<int>(2)));
        unordered_set<int> ignore(cbegin(graph[HOLE]), cend(graph[HOLE]));
        for (int m = 0; m < size(graph); ++m) {
            for (int c = 0; c < size(graph); ++c) {
                degree[m][c][MOUSE - 1] = size(graph[m]);
                degree[m][c][CAT - 1] = size(graph[c]) - ignore.count(c);
            }
        }
        vector<vector<vector<int>>> color(size(graph), vector<vector<int>>(size(graph), vector<int>(2)));
        queue<tuple<int, int, int>> q1;
        queue<tuple<int, int, int>> q2;
        for(int i = 0; i < size(graph); ++i) {
            if (i == HOLE) {
                continue;
            }
            color[HOLE][i][CAT - 1] = MOUSE;
            q1.emplace(HOLE, i, CAT);
            for (const auto& t : {MOUSE, CAT}) {
                color[i][i][t - 1] = CAT;
                q2.emplace(i, i, t);
            }
        }
        while (!empty(q1)) {
            const auto [i, j, t] = q1.front(); q1.pop();
            for (const auto& [ni, nj, nt] : parents(graph, i, j, t)) {
                if (color[ni][nj][nt - 1] != DRAW) {
                    continue;
                }
                if (t == CAT) {
                    color[ni][nj][nt - 1] = MOUSE;
                    q1.emplace(ni, nj, nt);
                    continue;
                }
                --degree[ni][nj][nt - 1];
                if (!degree[ni][nj][nt - 1]) {
                    color[ni][nj][nt - 1] = MOUSE;
                    q1.emplace(ni, nj, nt);
                }
            }
        }
        while (!empty(q2)) {
            const auto [i, j, t] = q2.front(); q2.pop();
            for (const auto& [ni, nj, nt] : parents(graph, i, j, t)) {
                if (color[ni][nj][nt - 1] != DRAW) {
                    continue;
                }
                if (t == MOUSE) {
                    color[ni][nj][nt - 1] = CAT;
                    q2.emplace(ni, nj, nt);
                    continue;
                }
                --degree[ni][nj][nt - 1];
                if (!degree[ni][nj][nt - 1]) {
                    color[ni][nj][nt - 1] = CAT;
                    q2.emplace(ni, nj, nt);
                }
            }
        }
        return color[MOUSE_START][CAT_START][MOUSE - 1];
    }

