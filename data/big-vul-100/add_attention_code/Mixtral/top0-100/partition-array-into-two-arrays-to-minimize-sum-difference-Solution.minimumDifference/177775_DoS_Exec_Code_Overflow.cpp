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

    int minimumDifference(vector<int>& nums) {
        vector<int> left, right; 
        for (int i = 0; i < size(nums); ++i) {
            if (i < size(nums) / 2) {
                left.emplace_back(nums[i]); 
            } else {
                right.emplace_back(nums[i]); 
            }
        }
        const auto& total1 = accumulate(cbegin(left), cend(left), 0);
        const auto& total2 = accumulate(cbegin(right), cend(right), 0);
        const int bound = (1 << size(left));
        unordered_map<int, vector<int>> sums;
        for (int mask = 0; mask < bound; ++mask) {
            int total = 0, bit = 1;
            for (const auto& x : left) {
                if (mask & bit) {
                    total += x; 
                }
                bit <<= 1;
            }
            sums[__builtin_popcount(mask)].emplace_back(2 * total - total1); 
        }
        for (auto& [_, v] : sums) {
            sort(begin(v), end(v));
        }
        int result = numeric_limits<int>::max();
        for (int mask = 0; mask < bound; ++mask) {
            int total = 0, bit = 1;
            for (const auto& x : right) {
                if (mask & bit) {
                    total += x; 
                }
                bit <<= 1;
            }
            const int k = size(right) - __builtin_popcount(mask);
            const int diff = 2 * total - total2; 
            const auto cit = lower_bound(cbegin(sums[k]), cend(sums[k]), -diff); 
            if (cit != cend(sums[k])) {
                result = min(result, abs(*cit + diff)); 
            }
            if (cit != cbegin(sums[k])) {
                result = min(result, abs(*prev(cit) + diff));    
            }
        }
        return result; 
    }

