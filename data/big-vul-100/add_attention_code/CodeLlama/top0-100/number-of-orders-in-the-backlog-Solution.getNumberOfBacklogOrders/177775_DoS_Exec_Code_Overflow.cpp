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


    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        static const int MOD = 1e9 + 7;

        priority_queue<vector<int>> buy;  // max_heap
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> sell;  // min_heap
        for (const auto& o : orders) {
            if (o[2] == 0) {
                buy.emplace(o);
            } else {
                sell.emplace(o);
            }
            while (!empty(buy) && !empty(sell) && sell.top()[0] <= buy.top()[0]) {
                int k = min(buy.top()[1], sell.top()[1]);
                auto tmp = buy.top(); buy.pop();
                tmp[1] -= k;
                if (tmp[1]) {
                    buy.emplace(tmp);
                }
                tmp = sell.top(); sell.pop();
                tmp[1] -= k;
                if (tmp[1]) {
                    sell.emplace(tmp);
                }
            }

        }
        int result = 0;
        while (!empty(buy)) {
            result = (result + buy.top()[1]) % MOD; buy.pop();
        }
        while (!empty(sell)) {
            result = (result + sell.top()[1]) % MOD; sell.pop();
        }
        return result;
    }


