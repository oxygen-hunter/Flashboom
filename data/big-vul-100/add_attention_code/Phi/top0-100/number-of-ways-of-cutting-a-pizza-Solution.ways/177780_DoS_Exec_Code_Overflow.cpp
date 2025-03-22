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

    int ways(vector<string>& pizza, int k) {
        static int MOD = 1e9 + 7;
        vector<vector<int>> prefix(pizza.size(), vector<int>(pizza[0].size()));
        for (int j = pizza[0].size() - 1; j >= 0; --j) {
            for (int accu = 0, i = pizza.size() - 1; i >= 0; --i) {
                accu += pizza[i][j] == 'A';
                prefix[i][j] = ((j + 1 != pizza[0].size()) ? prefix[i][j + 1] : 0) + accu;
            }
        }
        vector<vector<vector<uint64_t>>> dp(pizza.size(),
                                            vector<vector<uint64_t>>(pizza[0].size(),
                                            vector<uint64_t>(k)));
        for (int i = pizza.size() - 1; i >= 0; --i) {
            for (int j = pizza[0].size() - 1; j >= 0; --j) {
                dp[i][j][0] = 1;
                for (int m = 1; m < k; ++m) {
                    for (int n = i + 1; n < pizza.size() && prefix[n][j]; ++n) {
                        if (prefix[i][j] == prefix[n][j]) {
                            continue;
                        }
                        dp[i][j][m] = (dp[i][j][m] + dp[n][j][m - 1]) % MOD;
                    }
                    for (int n = j + 1; n < pizza[0].size() && prefix[i][n]; ++n) {
                        if (prefix[i][j] == prefix[i][n]) {
                            continue;
                        }
                        dp[i][j][m] = (dp[i][j][m] + dp[i][n][m - 1]) % MOD;
                    }
                }
            }
        }
        return dp[0][0][k - 1];
    }

