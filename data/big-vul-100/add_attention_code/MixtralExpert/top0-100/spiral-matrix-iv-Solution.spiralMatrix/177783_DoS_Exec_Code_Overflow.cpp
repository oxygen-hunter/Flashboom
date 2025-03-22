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


    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        static const vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        vector<vector<int>> result(m, vector<int>(n, -1));
        for (int i = 0, j = 0, d = 0; head; head = head->next) {
            result[i][j] = head->val;
            if (!(0 <= i + directions[d].first && i + directions[d].first < m &&
                  0 <= j + directions[d].second && j + directions[d].second < n &&
                  result[i + directions[d].first][j + directions[d].second] == -1)) {
                d = (d + 1) % 4;
            }
            i += directions[d].first;
            j += directions[d].second;
        }
        return result;
    }


