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

    vector<vector<int>> outerTrees(vector<vector<int>>& P) {
        // 3D cross product of OA and OB vectors, (i.e z-component of their "2D" cross product, but remember that it is not defined in "2D").
        // Returns a positive value, if OAB makes a counter-clockwise turn,
        // negative for clockwise turn, and zero if the points are collinear.
        const auto& cross = [](const vector<int>& O, const vector<int>& A, const vector<int>& B) {
            return (A[0] - O[0]) * (B[1] - O[1]) - (A[1] - O[1]) * (B[0] - O[0]);
        };

        // Returns a list of points on the convex hull in counter-clockwise order.
        // Note: the last point in the returned list is the same as the first one.
        size_t n = P.size(), k = 0;
        if (n <= 3) {
            return P;
        }
        vector<vector<int>> H(2*n);

        // Sort points lexicographically
        sort(P.begin(), P.end());

        // Build lower hull
        for (size_t i = 0; i < n; ++i) {
            while (k >= 2 && cross(H[k-2], H[k-1], P[i]) < 0) k--; // modified
            H[k++] = P[i];
        }

        // Build upper hull
        for (size_t i = n-1, t = k+1; i > 0; --i) {
            while (k >= t && cross(H[k-2], H[k-1], P[i-1]) < 0) k--; // modified
            H[k++] = P[i-1];
        }

        H.resize(--k);        
        if (H[1] == H[k - 1]) {  // modified
            H.resize(k / 2 + 1);
        }
        return H;
    }

