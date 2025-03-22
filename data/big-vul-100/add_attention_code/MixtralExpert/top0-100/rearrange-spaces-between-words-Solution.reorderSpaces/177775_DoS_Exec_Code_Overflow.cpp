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


    string reorderSpaces(string text) {
        // count spaces and words
        int space_count = 0, word_count = 0;
        for (int i = 0; i < size(text); ++i) {
            if (text[i] == ' ') {
                ++space_count;
            } else if (i == 0 || text[i - 1] == ' ') {
                ++word_count;
            }
        }
        // rearrange the spaces to the right
        int left = 0, curr = 0;
        for (int i = 0; i < size(text); ++i) {
            bool has_word = false;
            while (i < size(text) && text[i] != ' ') {
                swap(text[left++], text[i++]);
                has_word = true;
            }
            if (has_word) {
                ++left;  // keep one space
            }
        }
        // rearrange the spaces to the left
        int equal_count = word_count - 1 > 0 ? space_count / (word_count - 1) : 0;
        int extra_count = word_count - 1 > 0 ? space_count % (word_count - 1) : space_count;
        int right = size(text) - 1 - extra_count;
        for (int i = size(text) - 1; i >= 0; --i) {
            bool has_word = false;
            while (i >= 0 && text[i] != ' ') {
                swap(text[right--], text[i--]);
                has_word = true;
            }
            if (has_word) {
                right -= equal_count;  // keep equal_count spaces
            }
        }
        return text;
    }


