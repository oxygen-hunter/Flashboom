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

    long long maximumScore(vector<vector<int>>& grid) {
        vector<int64_t> prefix(size(grid)+ 1);
        for (int i = 0; i < size(grid); ++i) {
            prefix[i + 1] = prefix[i] + grid[i][0];
        }
        // dp[0][i]: the maximum score from 0 to the current column, and the current column has i black cells, without scoring the white cells of the current column
        // dp[1][i]: the maximum score from 0 to the current column, and the current column has i black cells, with scoring the white cells of the current column
        vector<vector<int64_t>> dp(2, vector<int64_t>(size(grid) + 1));
        for (int j = 1; j < size(grid[0]); ++j) {
            vector<int64_t> new_prefix(size(grid)+ 1);
            for (int i = 0; i < size(grid); ++i) {
                new_prefix[i + 1] = new_prefix[i] + grid[i][j];
            }
            vector<vector<int64_t>> new_dp(2, vector<int64_t>(size(grid) + 1));
            for (int i = 0; i <= size(grid); ++i) {
                for (int k = 0; k <= size(grid); ++k) {
                    new_dp[0][i] = max(new_dp[0][i], max(prefix[i] - prefix[k], static_cast<int64_t>(0)) + dp[0][k]);
                    new_dp[1][i] = max(new_dp[1][i], dp[1][k] + max(new_prefix[k] - new_prefix[i], static_cast<int64_t>(0)));
                }
                new_dp[0][i] = max(new_dp[0][i], ranges::max(dp[1]));
                new_dp[1][i] = max(new_dp[1][i], new_dp[0][i]);
            }
            dp = move(new_dp);
            prefix = move(new_prefix);
        }
        return ranges::max(dp[1]);
    }

