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


        void sortColors(int A[], int n) {
            int red = 0;
            int blue = n-1;
            for(int i = 0; i < blue + 1;) {
                if(A[i] == 0) {
                    swap(A[i++], A[red++]);
                }
                else if(A[i] == 2) {
                    swap(A[i], A[blue--]);
                }
                else {
                    i++;
                }
            }
        }


