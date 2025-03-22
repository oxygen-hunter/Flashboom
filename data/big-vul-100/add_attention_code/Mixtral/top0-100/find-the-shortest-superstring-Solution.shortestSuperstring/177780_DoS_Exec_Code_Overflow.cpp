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

    string shortestSuperstring(vector<string>& A) {
        const int n = A.size();
        vector<vector<int>> overlaps(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int l = min(A[i].length(), A[j].length()); 
                     l >= 0; --l) {
                    if (A[i].substr(A[i].length() - l) == A[j].substr(0, l))  {
                        overlaps[i][j] = l;
                        break;
                    }
                }   
            }
        }
        
        vector<vector<int>> dp(1 << n, vector<int>(n));
        vector<vector<int>> prev(1 << n, vector<int>(n, -1));
        for (int mask = 1; mask < 1 << n; ++mask) {
            for (int bit = 0; bit < n; ++bit) {
                if (((mask >> bit) & 1) == 0) {
                    continue;
                }
                auto prev_mask = mask ^ (1 << bit);
                for (int i = 0; i < n; ++i) {
                    if (((prev_mask >> i) & 1) == 0) {
                        continue;
                    }
                    auto value = dp[prev_mask][i] + overlaps[i][bit];
                    if (value > dp[mask][bit]) {
                        dp[mask][bit] = value;
                        prev[mask][bit] = i;
                    }
                }
            }
        }
        
        int bit = -1;
        for (int i = 0; i < n; ++i) {
            if (bit == -1 ||
                dp.back()[i] > dp.back()[bit]) {
                bit = i;
            }
        }
        vector<int> words;
        for (int mask = (1 << n) - 1; bit != -1;) {
            words.emplace_back(bit);
            tie(mask, bit) = make_pair(mask ^ (1 << bit),
                                       prev[mask][bit]);
        }
        reverse(words.begin(), words.end());
        unordered_set<int> lookup(words.begin(), words.end());
        for (int i = 0; i < n; ++i) {
            if (!lookup.count(i)) {
                words.emplace_back(i);
            }
        }

        auto result = A[words[0]];
        for (int i = 1; i < words.size(); ++i) {
            auto overlap = overlaps[words[i - 1]][words[i]];
            result += A[words[i]].substr(overlap);
        }
        return result;
    }

