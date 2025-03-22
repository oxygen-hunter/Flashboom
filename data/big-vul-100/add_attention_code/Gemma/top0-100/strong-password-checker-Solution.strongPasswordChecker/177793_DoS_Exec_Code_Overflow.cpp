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


    int strongPasswordChecker(string s) {
        int missing_type_cnt = 3;
        missing_type_cnt -= static_cast<int>(any_of(s.begin(), s.end(), [](char c){ return isdigit(c); }));
        missing_type_cnt -= static_cast<int>(any_of(s.begin(), s.end(), [](char c){ return isupper(c); }));
        missing_type_cnt -= static_cast<int>(any_of(s.begin(), s.end(), [](char c){ return islower(c); }));

        int total_change_cnt = 0;
        int one_change_cnt = 0, two_change_cnt = 0, three_change_cnt = 0;
        for (int i = 2; i < s.length();) {
            if (s[i] == s[i - 1] && s[i - 1] == s[i - 2]) {
                int length = 2;
                while (i < s.length() && s[i] == s[i - 1]) {
                    ++length;
                    ++i;
                }
                total_change_cnt += length / 3;
                if (length % 3 == 0) {
                    ++one_change_cnt;
                } else if (length % 3 == 1) {
                    ++two_change_cnt;
                } else {
                    ++three_change_cnt;
                }
            } else {
                ++i;
            }
        }

        if (s.length() < 6) {
            return max(missing_type_cnt, 6 - static_cast<int>(s.length()));
        } else if (s.length() <= 20) {
            return max(missing_type_cnt, total_change_cnt);
        }

        int delete_cnt = s.length() - 20;
        
        total_change_cnt -= min(delete_cnt, one_change_cnt) / 1;
        total_change_cnt -= min(max(delete_cnt - one_change_cnt, 0), two_change_cnt * 2) / 2;
        total_change_cnt -= min(max(delete_cnt - one_change_cnt - 2 * two_change_cnt, 0), three_change_cnt * 3) / 3;
            
        return delete_cnt + max(missing_type_cnt, total_change_cnt);
    }


