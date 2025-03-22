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


        bool isInterleave(string s1, string s2, string s3) {
            if(s1.length() + s2.length() != s3.length()) return false;

            if(s1.length() < s2.length()) return isInterleave(s2, s1, s3);

            vector<bool> f(s2.length() + 1, true);

            for(auto j = 1; j <= s2.length(); ++j) {
                f[j] = f[j - 1] && s2[j - 1] == s3[j - 1];
            }

            for(auto i = 1; i <= s1.length(); ++i) {
                f[0] = f[0] && s1[i - 1] == s3[i - 1];
                for(auto j = 1; j <= s2.length(); ++j) {
                    f[j] = (f[j] && s1[i - 1] == s3[i + j - 1])
                        || (f[j - 1] && s2[j - 1] == s3[i + j - 1]);
                }
            }

            return f[s2.length()];
        }


