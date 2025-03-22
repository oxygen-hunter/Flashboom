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

    int catMouseGame(vector<vector<int>>& graph) {
        vector<vector<vector<int>>> degree(size(graph), vector<vector<int>>(size(graph), vector<int>(2)));
        unordered_set<int> ignore(cbegin(graph[HOLE]), cend(graph[HOLE]));
        for (int m = 0; m < size(graph); ++m) {
            for (int c = 0; c < size(graph); ++c) {
                degree[m][c][MOUSE - 1] = size(graph[m]);
                degree[m][c][CAT - 1] = size(graph[c]) - ignore.count(c);
            }
        }
        vector<vector<vector<int>>> color(size(graph), vector<vector<int>>(size(graph), vector<int>(2)));
        queue<tuple<int, int, int>> q1;
        queue<tuple<int, int, int>> q2;
        for(int i = 0; i < size(graph); ++i) {
            if (i == HOLE) {
                continue;
            }
            color[HOLE][i][CAT - 1] = MOUSE;
            q1.emplace(HOLE, i, CAT);
            for (const auto& t : {MOUSE, CAT}) {
                color[i][i][t - 1] = CAT;
                q2.emplace(i, i, t);
            }
        }
        while (!empty(q1)) {
            const auto [i, j, t] = q1.front(); q1.pop();
            for (const auto& [ni, nj, nt] : parents(graph, i, j, t)) {
                if (color[ni][nj][nt - 1] != DRAW) {
                    continue;
                }
                if (t == CAT) {
                    color[ni][nj][nt - 1] = MOUSE;
                    q1.emplace(ni, nj, nt);
                    continue;
                }
                --degree[ni][nj][nt - 1];
                if (!degree[ni][nj][nt - 1]) {
                    color[ni][nj][nt - 1] = MOUSE;
                    q1.emplace(ni, nj, nt);
                }
            }
        }
        while (!empty(q2)) {
            const auto [i, j, t] = q2.front(); q2.pop();
            for (const auto& [ni, nj, nt] : parents(graph, i, j, t)) {
                if (color[ni][nj][nt - 1] != DRAW) {
                    continue;
                }
                if (t == MOUSE) {
                    color[ni][nj][nt - 1] = CAT;
                    q2.emplace(ni, nj, nt);
                    continue;
                }
                --degree[ni][nj][nt - 1];
                if (!degree[ni][nj][nt - 1]) {
                    color[ni][nj][nt - 1] = CAT;
                    q2.emplace(ni, nj, nt);
                }
            }
        }
        return color[MOUSE_START][CAT_START][MOUSE - 1];
    }

