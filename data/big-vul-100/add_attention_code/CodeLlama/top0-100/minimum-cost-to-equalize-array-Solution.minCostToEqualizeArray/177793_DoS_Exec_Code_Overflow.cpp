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


    int minCostToEqualizeArray(vector<int>& nums, int cost1, int cost2) {
        static const int MOD = 1e9 + 7;

        const int n = size(nums);
        const int64_t mx = ranges::max(nums);
        int64_t total = mx * n - accumulate(cbegin(nums), cend(nums), 0ll);
        // fill until mx with only cost1 operations
        if (n <= 2 || 2 * cost1 <= cost2) {
            return total * cost1 % MOD;
        }

        int64_t result = numeric_limits<int64_t>::max();
        // fill until mx with more cost2 operations and fewer cost1 operations
        const int64_t mn = ranges::min(nums);
        int64_t cnt1 = max((mx - mn) - (total - (mx - mn)), static_cast<int64_t>(0));
        int64_t cnt2 = total - cnt1;
        result = min(result, (cnt1 + cnt2 % 2) * cost1 + cnt2 / 2 * cost2);

        // fill until mx+x with most cost2 operations and fewest cost1 operations,
        // where x is the max of x s.t. cnt1+x >= (n-1)*x => cnt1 >= (n-2)*x
        const int64_t x = cnt1 / (n - 2);
        cnt1 %= n - 2;
        total += n * x;
        cnt2 = total - cnt1;
        result = min(result, (cnt1 + cnt2 % 2) * cost1 + (cnt2 / 2) * cost2);

        // fill until mx+x+1 or mx+x+2 with nearly all cost2 operations and at most one cost1 operation
        for (int _ = 0; _ < 2; ++_) {  // increase twice is for odd n
            total += n;
            result = min(result, total % 2 * cost1 + total / 2 * cost2);
        }
        return result % MOD;
    }


