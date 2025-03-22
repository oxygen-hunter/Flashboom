GBool SplashFTFont::makeGlyph(int c, int xFrac, int yFrac,
			      SplashGlyphBitmap *bitmap, int x0, int y0, SplashClip *clip, SplashClipResult *clipRes) {
  SplashFTFontFile *ff;
  FT_Vector offset;
  FT_GlyphSlot slot;
  FT_UInt gid;
  int rowSize;
  Guchar *p, *q;
  int i;

  ff = (SplashFTFontFile *)fontFile;

  ff->face->size = sizeObj;
  offset.x = (FT_Pos)(int)((SplashCoord)xFrac * splashFontFractionMul * 64);
  offset.y = 0;
  FT_Set_Transform(ff->face, &matrix, &offset);
  slot = ff->face->glyph;

  if (ff->codeToGID && c < ff->codeToGIDLen) {
    gid = (FT_UInt)ff->codeToGID[c];
  } else {
    gid = (FT_UInt)c;
  }
  if (ff->trueType && gid == 0) {
    return gFalse;
  }

#ifdef TT_CONFIG_OPTION_BYTECODE_INTERPRETER
  if (FT_Load_Glyph(ff->face, gid,
		    aa ? FT_LOAD_NO_BITMAP : FT_LOAD_DEFAULT)) {
    return gFalse;
  }
#else
  if (FT_Load_Glyph(ff->face, gid,
		    aa ? FT_LOAD_NO_HINTING | FT_LOAD_NO_BITMAP
                       : FT_LOAD_DEFAULT)) {
    return gFalse;
  }
#endif

  FT_Glyph_Metrics *glyphMetrics = &(ff->face->glyph->metrics);
  bitmap->x = splashRound(-glyphMetrics->horiBearingX / 64.0);
  bitmap->y = splashRound(glyphMetrics->horiBearingY / 64.0);
  bitmap->w = splashRound(glyphMetrics->width / 64.0);
  bitmap->h = splashRound(glyphMetrics->height / 64.0);

  *clipRes = clip->testRect(x0 - bitmap->x,
                            y0 - bitmap->y,
                            x0 - bitmap->x + bitmap->w,
                            y0 - bitmap->y + bitmap->h);
  if (*clipRes == splashClipAllOutside) {
    bitmap->freeData = gFalse;
    return gTrue;
  }

  if (FT_Render_Glyph(slot, aa ? ft_render_mode_normal
		               : ft_render_mode_mono)) {
    return gFalse;
  }

  bitmap->x = -slot->bitmap_left;
  bitmap->y = slot->bitmap_top;
  bitmap->w = slot->bitmap.width;
  bitmap->h = slot->bitmap.rows;
  bitmap->aa = aa;
  if (aa) {
    rowSize = bitmap->w;
   } else {
     rowSize = (bitmap->w + 7) >> 3;
   }
  bitmap->data = (Guchar *)gmalloc(rowSize * bitmap->h);
   bitmap->freeData = gTrue;
   for (i = 0, p = bitmap->data, q = slot->bitmap.buffer;
        i < bitmap->h;
       ++i, p += rowSize, q += slot->bitmap.pitch) {
    memcpy(p, q, rowSize);
  }

  return gTrue;
}


    int distinctSequences(int n) {
        static const int MOD = 1e9 + 7;
        if (n == 1) {
            return 6;
        }
        vector<vector<int>> dp(6, vector<int>(6));
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                if (i != j && gcd(i + 1, j + 1) == 1) {
                    dp[i][j] = 1;
                }
            }
        }
        for (int _ = 0; _ < n - 2; ++_) {
            vector<vector<int>> new_dp(6, vector<int>(6));
            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 6; ++j) {
                    if (!dp[i][j]) {
                        continue;
                    }
                    for (int k = 0; k < 6; ++k) {
                        if (!dp[j][k]) {
                            continue;
                        }
                        if (k != i) {
                            new_dp[i][j] = (new_dp[i][j] + dp[j][k]) % MOD;
                        }
                    }
                }
            }
            dp = move(new_dp);
        }
        return accumulate(cbegin(dp), cend(dp), 0,
                          [&](int total, const auto& x) {
                              return (total + accumulate(cbegin(x), cend(x), 0,
                                                         [&](int total, int x) {
                                                             return (total + x) % MOD;
                                                         })) % MOD;
                          });
    }


