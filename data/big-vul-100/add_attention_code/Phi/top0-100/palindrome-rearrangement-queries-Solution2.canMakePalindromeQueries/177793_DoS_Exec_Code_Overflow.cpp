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

    vector<bool> canMakePalindromeQueries(string s, vector<vector<int>>& queries) {
        vector<int> prefix(size(s) / 2 + 1);
        vector<vector<int>> prefixs1(size(s) / 2 + 1, vector<int>(26));
        vector<vector<int>> prefixs2(size(s) / 2 + 1, vector<int>(26));
        for (int i = 0; i < size(s) / 2; ++i) {
            const int x = s[i] - 'a', y = s[(size(s) - 1) - i] - 'a';
            prefix[i + 1] = prefix[i] + (x != y ? 1 : 0);
            for (int j = 0; j < 26; ++j) {
                prefixs1[i + 1][j] = prefixs1[i][j] + (j == x ? 1 : 0);
                prefixs2[i + 1][j] = prefixs2[i][j] + (j == y ? 1 : 0);
            }
        }
    
        const auto& check = [&](int left1, int right1, int left2, int right2) {
            const auto& same = [&](int left, int right) {
                for (int i = 0; i < 26; ++i) {
                    if ((prefixs1[right + 1][i] - prefixs1[left][i]) - (prefixs2[right + 1][i] - prefixs1[left][i]) != 0) {
                        return false;
                    }
                }
                return true;
            };

            const auto& min_left = min(left1, left2), &max_left = max(left1, left2);
            const auto& min_right = min(right1, right2), &max_right = max(right1, right2);
            if (!(prefix[min_left] - prefix[0] == 0 && prefix.back() - prefix[max_right + 1] == 0)) {
                return false;
            }
            if (min_right < max_left) {  // non-overlapped
                return prefix[max_left] - prefix[min_right + 1] == 0 && same(min_left, min_right) && same(max_left, max_right);
            }
            // overlapped
            if ((left1 == min_left) == (right1 == max_right)) {  // inside another
                return same(min_left, max_right);
            }
            // not inside another
            auto p1 = &prefixs1, p2 = &prefixs2;
            if (min_left != left1) {
                swap(p1, p2);
            }
            for (int i = 0; i < 26; ++i) {
                const int d1 = ((*p1)[min_right + 1][i] - (*p1)[min_left][i]) - ((*p2)[max_left][i] - (*p2)[min_left][i]);
                const int d2 = ((*p2)[max_right + 1][i] - (*p2)[max_left][i]) - ((*p1)[max_right + 1][i] - (*p1)[min_right + 1][i]);
                if (!(d1 == d2 && d1 >= 0)) {  // test case: s = "aabbba", queries = [[0,1,3,4]]
                    return false;
                }
            }
            return true;
        };
    
        vector<bool> result(size(queries));
        for (int i = 0; i < size(queries); ++i) {
            result[i] = check(queries[i][0], queries[i][1], (size(s) - 1) - queries[i][3], (size(s) - 1) - queries[i][2]);
        }
        return result;
    }

