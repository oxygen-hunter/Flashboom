  tt_cmap10_validate( FT_Byte*      table,
                      FT_Validator  valid )
  {
    FT_Byte*  p = table + 4;
    FT_ULong  length, count;


    if ( table + 20 > valid->limit )
      FT_INVALID_TOO_SHORT;

    length = TT_NEXT_ULONG( p );
     p      = table + 16;
     count  = TT_NEXT_ULONG( p );
 
    if ( table + length > valid->limit || length < 20 + count * 2 )
       FT_INVALID_TOO_SHORT;
 
     /* check glyph indices */
    {
      FT_UInt  gindex;


      for ( ; count > 0; count-- )
      {
        gindex = TT_NEXT_USHORT( p );
        if ( gindex >= TT_VALID_GLYPH_COUNT( valid ) )
          FT_INVALID_GLYPH_ID;
      }
    }

    return SFNT_Err_Ok;
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


