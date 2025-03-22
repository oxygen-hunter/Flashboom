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

    int maximumMinutes(vector<vector<int>>& grid) {
        static const vector<pair<int, int>> directions{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        enum State {FIRE = 1, WALL, PERSON};
        const int INF = 1e9;
        const auto& bfs = [&]() {
            unordered_map<int, vector<vector<int>>> time;
            time[FIRE] = vector<vector<int>>(size(grid), vector<int>(size(grid[0]), INF));
            time[PERSON] = vector<vector<int>>(size(grid), vector<int>(size(grid[0]), INF));
            vector<tuple<int, int, int>> q;
            for (int r = 0; r < size(grid); ++r) {
                for (int c = 0; c < size(grid[0]); ++c) {
                    if (grid[r][c] == FIRE) {
                        q.emplace_back(r, c, FIRE);
                    }
                }
            }
            q.emplace_back(0, 0, PERSON);
            for (const auto& [r, c, t] : q) {
                time[t][r][c] = 0;
            }
            for (int d = 0; !empty(q); ++d) {
                vector<tuple<int, int, int>> new_q;
                for (const auto& [r, c, t] : q) {
                    for (const auto& [dr, dc] : directions) {
                        const int nr = r + dr, nc = c + dc;
                        if (!(0 <= nr && nr < size(grid) && 0 <= nc && nc < size(grid[0]) &&
                              grid[nr][nc] != WALL && time[t][nr][nc] == INF &&
                              (t == FIRE ||
                               d + 1 < time[FIRE][nr][nc] || (d + 1 == time[FIRE][nr][nc] && nr == size(grid) - 1 && nc == size(grid[0]) - 1)))) {
                            continue;
                        }
                        time[t][nr][nc] = d + 1;
                        new_q.emplace_back(nr, nc, t);
                    }
                }
                q = move(new_q);
            }
            return time;
        };
        auto time = bfs();
        if (time[PERSON][size(grid) - 1][size(grid[0]) - 1] == INF) {
            return -1;
        }
        if (time[FIRE][size(grid) - 1][size(grid[0]) - 1] == INF) {
            return INF;
        }
        const int diff = time[FIRE][size(grid) - 1][size(grid[0]) - 1] - time[PERSON][size(grid) - 1][size(grid[0]) - 1];
        return (time[FIRE][size(grid) - 1][size(grid[0]) - 2] - time[PERSON][size(grid) - 1][size(grid[0]) - 2] == diff + 2 ||
                time[FIRE][size(grid) - 2][size(grid[0]) - 1] - time[PERSON][size(grid) - 2][size(grid[0]) - 1] == diff + 2)
               ? diff
               : diff - 1;
    }

