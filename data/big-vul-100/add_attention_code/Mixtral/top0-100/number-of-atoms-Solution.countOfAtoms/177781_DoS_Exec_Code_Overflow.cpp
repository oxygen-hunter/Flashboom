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

    string countOfAtoms(string formula) {
        stack<map<string, int>> stk;
        stk.emplace();
        int submatches[] = { 1, 2, 3, 4, 5 };
        const auto e = regex("([A-Z][a-z]*)(\\d*)|(\\()|(\\))(\\d*)");
        for (regex_token_iterator<string::iterator> it(formula.begin(), formula.end(), e, submatches), end;
             it != end;) {
            const auto& name = (it++)->str();
            const auto& m1 = (it++)->str();
            const auto& left_open = (it++)->str();
            const auto& right_open = (it++)->str();
            const auto& m2 = (it++)->str();
            if (!name.empty()) {
                stk.top()[name] += stoi(!m1.empty() ? m1 : "1");
            }
            if (!left_open.empty()) {
                stk.emplace();
            }
            if (!right_open.empty()) {
                const auto top = move(stk.top()); stk.pop();
                for (const auto& kvp: top) {
                    stk.top()[kvp.first] += kvp.second * stoi(!m2.empty() ? m2 : "1");
                }
            }
        }
        string result;
        for (const auto& kvp : stk.top()) {
            result += kvp.first;
            if (kvp.second > 1) {
                result += to_string(kvp.second);
            }
        }
        return result;
    }

