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

    int maximumScore(vector<int>& nums, int k) {
        static const int MOD = 1e9 + 7;
        const auto& addmod = [&](uint32_t a, uint32_t b) {  // avoid overflow
            a %= MOD, b %= MOD;
            if (MOD - a <= b) {
                b -= MOD;  // relied on unsigned integer overflow in order to give the expected results
            }
            return a + b;
        };

        const auto& mulmod = [&](uint32_t a, uint32_t b)  {  // avoid overflow
            a %= MOD, b %= MOD;
            uint32_t result = 0;
            if (a < b) {
                swap(a, b);
            }
            while (b > 0)  { 
                if (b % 2 == 1) {
                    result = addmod(result, a);
                }
                a = addmod(a, a);
                b /= 2; 
            } 
            return result; 
        };

        const auto& powmod = [&](uint32_t a, uint32_t b) {
            a %= MOD;
            uint32_t result = 1;
            while (b) {
                if (b & 1) {
                    result = mulmod(result, a);
                }
                a = mulmod(a, a);
                b >>= 1;
            }
            return result;
        };
    
        const auto& linear_sieve_of_eratosthenes = [](int n) {  // Time: O(n), Space: O(n)
            vector<int> spf(n + 1, -1);
            vector<int> primes;
            for (int i = 2; i <= n; ++i) {
                if (spf[i] == -1) {
                    spf[i] = i;
                    primes.emplace_back(i);
                }
                for (const auto& p : primes) {
                    if (i * p > n || p > spf[i]) {
                        break;
                    }
                    spf[i * p] = p;
                }
            }
            return primes;
        };
    
        const auto& primes = linear_sieve_of_eratosthenes(sqrt(*max_element(cbegin(nums), cend(nums))));
        unordered_map<int, int> lookup;
        const auto& count_of_distinct_prime_factors = [&](int x) {
            const int y = x;
            if (!lookup.count(y)) {
                int cnt = 0;
                for (const auto& p : primes) {
                    if (p * p > x) {
                        break;
                    }
                    if (x % p != 0) {
                        continue;
                    }
                    ++cnt;
                    for (; x % p == 0; x /= p);
                }
                if (x != 1) {
                    ++cnt;
                }
                lookup[y] = cnt;
            }
            return lookup[y];
        };

        vector<int> scores;
        scores.reserve(size(nums));
        for (const auto& x : nums) {
            scores.emplace_back(count_of_distinct_prime_factors(x));
        }

        vector<int> stk = {-1};
        vector<int> left(size(scores), -1);
        for (int i = 0; i < size(scores); ++i) {
            while (stk.back() != -1 && scores[stk.back()] < scores[i]) {  // if multiple such elements exist, choose the one with the smallest index
                stk.pop_back();
            }
            left[i] = stk.back();
            stk.emplace_back(i);
        }
        stk = {static_cast<int>(size(scores))};
        vector<int> right(size(scores), -1);
        for (int i =  size(scores) - 1; i >= 0; --i) {
            while (stk.back() != size(scores) && scores[stk.back()] <= scores[i]) {
                stk.pop_back();
            }
            right[i] = stk.back();
            stk.emplace_back(i);
        }

        int result = 1;
        vector<pair<int, int>> pairs;
        pairs.reserve(size(nums));
        for (int i = 0; i < size(nums); ++i) {
            pairs.emplace_back(nums[i], i);
        }
        priority_queue<pair<int, int>> max_heap(cbegin(pairs), cend(pairs));
        while (!empty(max_heap)) {
            const auto [_, i] = max_heap.top(); max_heap.pop();
            const int c = min((i - left[i]) * (right[i] - i), k);
            result = mulmod(result, powmod(nums[i], c));
            k -= c;
            if (!k) {
                break;
            }
        }
        return result;
    }

