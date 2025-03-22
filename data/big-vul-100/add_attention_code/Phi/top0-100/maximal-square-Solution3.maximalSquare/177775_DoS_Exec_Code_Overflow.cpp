void ArthurOutputDev::drawImage(GfxState *state, Object *ref, Stream *str,
				int width, int height,
				GfxImageColorMap *colorMap,
				int *maskColors, GBool inlineImg)
{
  unsigned char *buffer;
  unsigned int *dest;
  int x, y;
  ImageStream *imgStr;
  Guchar *pix;
  int i;
  double *ctm;
   QMatrix matrix;
   int is_identity_transform;
   
  buffer = (unsigned char *)gmalloc (width * height * 4);
 
   /* TODO: Do we want to cache these? */
   imgStr = new ImageStream(str, width,
			   colorMap->getNumPixelComps(),
			   colorMap->getBits());
  imgStr->reset();
  
  /* ICCBased color space doesn't do any color correction
   * so check its underlying color space as well */
  is_identity_transform = colorMap->getColorSpace()->getMode() == csDeviceRGB ||
		  (colorMap->getColorSpace()->getMode() == csICCBased && 
		  ((GfxICCBasedColorSpace*)colorMap->getColorSpace())->getAlt()->getMode() == csDeviceRGB);

  if (maskColors) {
    for (y = 0; y < height; y++) {
      dest = (unsigned int *) (buffer + y * 4 * width);
      pix = imgStr->getLine();
      colorMap->getRGBLine (pix, dest, width);

      for (x = 0; x < width; x++) {
	for (i = 0; i < colorMap->getNumPixelComps(); ++i) {
	  
	  if (pix[i] < maskColors[2*i] * 255||
	      pix[i] > maskColors[2*i+1] * 255) {
	    *dest = *dest | 0xff000000;
	    break;
	  }
	}
	pix += colorMap->getNumPixelComps();
	dest++;
      }
    }

    m_image = new QImage(buffer, width, height, QImage::Format_ARGB32);
  }
  else {
    for (y = 0; y < height; y++) {
      dest = (unsigned int *) (buffer + y * 4 * width);
      pix = imgStr->getLine();
      colorMap->getRGBLine (pix, dest, width);
    }

    m_image = new QImage(buffer, width, height, QImage::Format_RGB32);
  }

  if (m_image == NULL || m_image->isNull()) {
    qDebug() << "Null image";
    delete imgStr;
    return;
  }
  ctm = state->getCTM();
  matrix.setMatrix(ctm[0] / width, ctm[1] / width, -ctm[2] / height, -ctm[3] / height, ctm[2] + ctm[4], ctm[3] + ctm[5]);

  m_painter->setMatrix(matrix, true);
  m_painter->drawImage( QPoint(0,0), *m_image );
  delete m_image;
  m_image = 0;
  free (buffer);
  delete imgStr;

}

    int maximalSquare(vector<vector<char>>& A) {
        if (A.empty()) {
            return 0;
        }

        // DP table stores (h, w) for each (i, j).
        vector<vector<MaxHW>> table(A.size(), vector<MaxHW>(A.front().size()));
        for (int i = A.size() - 1; i >= 0; --i) {
            for (int j = A[i].size() - 1; j >= 0; --j) {
                // Find the largest h such that (i, j) to (i + h - 1, j) are feasible.
                // Find the largest w such that (i, j) to (i, j + w - 1) are feasible.
                table[i][j] = A[i][j] == '1'
                                  ? MaxHW{i + 1 < A.size() ? table[i + 1][j].h + 1 : 1,
                                          j + 1 < A[i].size() ? table[i][j + 1].w + 1 : 1}
                                  : MaxHW{0, 0};
            }
        }

        // A table stores the length of largest square for each (i, j).
        vector<vector<int>> s(A.size(), vector<int>(A.front().size(), 0));
        int max_square_area = 0;
        for (int i = A.size() - 1; i >= 0; --i) {
            for (int j = A[i].size() - 1; j >= 0; --j) {
                int side = min(table[i][j].h, table[i][j].w);
                if (A[i][j]) {
                    // Get the length of largest square with bottom-left corner (i, j).
                    if (i + 1 < A.size() && j + 1 < A[i + 1].size()) {
                        side = min(s[i + 1][j + 1] + 1, side);
                    }
                    s[i][j] = side;
                    max_square_area = max(max_square_area, side * side);
                }
            }
        }
        return max_square_area;
    }

