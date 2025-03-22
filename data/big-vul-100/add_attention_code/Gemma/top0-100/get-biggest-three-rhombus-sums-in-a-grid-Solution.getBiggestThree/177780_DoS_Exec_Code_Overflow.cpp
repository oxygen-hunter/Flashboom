GfxImageColorMap::GfxImageColorMap(int bitsA, Object *decode,
				   GfxColorSpace *colorSpaceA) {
  GfxIndexedColorSpace *indexedCS;
  GfxSeparationColorSpace *sepCS;
  int maxPixel, indexHigh;
  Guchar *lookup2;
  Function *sepFunc;
  Object obj;
  double x[gfxColorMaxComps];
  double y[gfxColorMaxComps];
  int i, j, k, byte;
  double mapped;

  ok = gTrue;

  bits = bitsA;
  maxPixel = (1 << bits) - 1;
  colorSpace = colorSpaceA;

  if (maxPixel > 255) maxPixel = 255;

  for (k = 0; k < gfxColorMaxComps; ++k) {
    lookup[k] = NULL;
  }

  if (decode->isNull()) {
    nComps = colorSpace->getNComps();
    colorSpace->getDefaultRanges(decodeLow, decodeRange, maxPixel);
  } else if (decode->isArray()) {
    nComps = decode->arrayGetLength() / 2;
    if (nComps != colorSpace->getNComps()) {
      goto err1;
    }
    for (i = 0; i < nComps; ++i) {
      decode->arrayGet(2*i, &obj);
      if (!obj.isNum()) {
	goto err2;
      }
      decodeLow[i] = obj.getNum();
      obj.free();
      decode->arrayGet(2*i+1, &obj);
      if (!obj.isNum()) {
	goto err2;
      }
      decodeRange[i] = obj.getNum() - decodeLow[i];
      obj.free();
    }
  } else {
    goto err1;
  }

  colorSpace2 = NULL;
  nComps2 = 0;
  if (colorSpace->getMode() == csIndexed) {
    indexedCS = (GfxIndexedColorSpace *)colorSpace;
    colorSpace2 = indexedCS->getBase();
    indexHigh = indexedCS->getIndexHigh();
     nComps2 = colorSpace2->getNComps();
     lookup2 = indexedCS->getLookup();
     colorSpace2->getDefaultRanges(x, y, indexHigh);
    byte_lookup = (Guchar *)gmalloc ((maxPixel + 1) * nComps2);
     for (k = 0; k < nComps2; ++k) {
       lookup[k] = (GfxColorComp *)gmallocn(maxPixel + 1,
 					   sizeof(GfxColorComp));
      for (i = 0; i <= maxPixel; ++i) {
	j = (int)(decodeLow[0] + (i * decodeRange[0]) / maxPixel + 0.5);
	if (j < 0) {
	  j = 0;
	} else if (j > indexHigh) {
	  j = indexHigh;
	}

	mapped = x[k] + (lookup2[j*nComps2 + k] / 255.0) * y[k];
	lookup[k][i] = dblToCol(mapped);
	byte_lookup[i * nComps2 + k] = (Guchar) (mapped * 255);
      }
    }
  } else if (colorSpace->getMode() == csSeparation) {
    sepCS = (GfxSeparationColorSpace *)colorSpace;
    colorSpace2 = sepCS->getAlt();
    nComps2 = colorSpace2->getNComps();
    sepFunc = sepCS->getFunc();
    byte_lookup = (Guchar *)gmallocn ((maxPixel + 1), nComps2);
    for (k = 0; k < nComps2; ++k) {
      lookup[k] = (GfxColorComp *)gmallocn(maxPixel + 1,
					   sizeof(GfxColorComp));
      for (i = 0; i <= maxPixel; ++i) {
	x[0] = decodeLow[0] + (i * decodeRange[0]) / maxPixel;
	sepFunc->transform(x, y);
	lookup[k][i] = dblToCol(y[k]);
	byte_lookup[i*nComps2 + k] = (Guchar) (y[k] * 255);
      }
    }
  } else {
    byte_lookup = (Guchar *)gmallocn ((maxPixel + 1), nComps);
    for (k = 0; k < nComps; ++k) {
      lookup[k] = (GfxColorComp *)gmallocn(maxPixel + 1,
					   sizeof(GfxColorComp));
      for (i = 0; i <= maxPixel; ++i) {
	mapped = decodeLow[k] + (i * decodeRange[k]) / maxPixel;
	lookup[k][i] = dblToCol(mapped);
	byte = (int) (mapped * 255.0 + 0.5);
	if (byte < 0)  
	  byte = 0;  
	else if (byte > 255)  
	  byte = 255;  
	byte_lookup[i * nComps + k] = byte;	
      }
    }
  }

  return;

 err2:
  obj.free();
 err1:
  ok = gFalse;
  byte_lookup = NULL;
}


    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        static const int K = 3;

        vector<vector<int>> left{grid}, right{grid};
        for (int i = 1; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]) - 1; ++j) {
                left[i][j] += left[i - 1][j + 1];
            }
        }
        for (int i = 1; i < size(grid); ++i) {
            for (int j = 1; j < size(grid[0]); ++j) {
                right[i][j] += right[i - 1][j - 1];
            }
        }
        priority_queue<int, vector<int>, greater<int>> min_heap;
        unordered_set<int> lookup;
        for (int k = 0; k <= (min(size(grid), size(grid[0])) + 1) / 2; ++k) {
            for (int i = k; i < size(grid) - k; ++i) {
                for (int j = k; j < size(grid[0]) - k; ++j) {
                    int total = k ? ((left[i][j - k] - left[i - k][j]) + (right[i][j + k] - right[i - k][j]) + grid[i - k][j]) +  
                                    ((left[i + k][j] - left[i][j + k]) + (right[i + k][j] - right[i][j - k]) - grid[i + k][j])
                                  : grid[i][j];
                    if (lookup.count(total)) {
                        continue;
                    }
                    lookup.emplace(total);
                    min_heap.emplace(total);
                    if (size(min_heap) == K + 1) {
                        lookup.erase(min_heap.top()); min_heap.pop();
                    }
                }
            }
        }
        vector<int> result;
        while (!empty(min_heap)) {
            result.emplace_back(min_heap.top()); min_heap.pop();
        }
        reverse(begin(result), end(result));
        return result;
    }


