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

    int numberOfSets(int n, int maxDistance, vector<vector<int>>& roads) {
        static const int INF = numeric_limits<int>::max();
        const auto& check = [&](int mask, const auto& dist) {
            for (int i = 0; i < n; ++i) {
                if ((mask & (1 << i)) == 0) {
                    continue;
                }
                for (int j = i + 1; j < n; ++j) {
                    if ((mask & (1 << j)) == 0) {
                        continue;
                    }
                    if (dist[i][j] > maxDistance) {
                        return false;
                    }
                }
            }
            return true;
        };

        const auto& floydWarshall = [&](int mask, auto dist) {
            for (int k = 0; k < n; ++k) {
                if ((mask & (1 << k)) == 0) {
                    continue;
                }
                for (int i = 0; i < n; ++i) {
                    if ((mask & (1 << i)) == 0) {  // optional, to speed up performance
                        continue;
                    }
                    for (int j = i + 1; j < n; ++j) {
                        if ((mask & (1 << j)) == 0) {  // optional, to speed up performance
                            continue;
                        }
                        if (dist[i][k] != INF && dist[k][j] != INF) {
                            dist[j][i] = dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                        }
                    }
                }
            }
            return check(mask, dist);
        };

        vector<vector<int>> dist(n, vector<int>(n, INF));
        for (int u = 0; u < n; ++u) {
            dist[u][u] = 0;
        }
        for (const auto& r : roads) {
            dist[r[0]][r[1]] = min(dist[r[0]][r[1]], r[2]);
            dist[r[1]][r[0]] = min(dist[r[1]][r[0]], r[2]);
        }
        int result = 0;
        for (int mask = 0; mask < (1 << n); ++mask) {
            result += floydWarshall(mask, dist);
        }
        return result;
    }

