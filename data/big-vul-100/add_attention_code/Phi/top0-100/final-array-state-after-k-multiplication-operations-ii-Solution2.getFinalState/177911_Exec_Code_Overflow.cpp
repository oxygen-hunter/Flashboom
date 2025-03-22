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

    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        static const double EPS = 1e-15;
        static const int MOD = 1e9 + 7;
        const auto& powmod = [&](int a, int b) {
            a %= MOD;
            int64_t result = 1;
            while (b) {
                if (b & 1) {
                    result = result * a % MOD;
                }
                a = int64_t(a) * a % MOD;
                b >>= 1;
            }
            return result;
        };

        const auto& binary_search_right = [](auto left, auto right, const auto& check) {
            while (left <= right) {
                const auto mid = left + (right - left) / 2;
                if (!check(mid)) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return right;
        };

        const auto& count = [](const auto& x, int target) {
            return static_cast<int>(target - x + EPS);
        };

        if (multiplier == 1) {
            return nums;
        }
        using P = pair<double, int>;
        vector<P> vals;
        for (int i = 0; i < size(nums); ++i) {
            vals.emplace_back(log(nums[i]) / log(multiplier), i);
        }
        sort(begin(vals), end(vals));
        const auto& check = [&](const auto& target) {
            int result = 0;
            for (const auto& [x, i] : vals) {
                const int c = count(x, target);
                if (c <= 0) {
                    break;
                }
                result += c;
            }
            return result <= k;
        };

        const int target = binary_search_right(1, static_cast<int>(vals.back().first) + 1, check);
        vector<int64_t> nums2(cbegin(nums), cend(nums));
        for (int idx = 0; idx < size(vals); ++idx) {
            const auto& [x, i] = vals[idx];
            const int c = count(x, target);
            if (c <= 0) {
                break;
            }
            k -= c;
            nums2[i] *= pow(multiplier, c);
        }
        using P2 = pair<int64_t, int>;
        vector<P2> vals2;
        for (int i = 0; i < size(nums2); ++i) {
            vals2.emplace_back(nums2[i], i);
        }
        sort(begin(vals2), end(vals2));
        const int q = k / size(nums), r = k % size(nums);
        const int m = powmod(multiplier, q);
        vector<int> result(size(nums));
        for (int idx = 0; idx < size(vals2); ++idx) {
            const auto& [x, i] = vals2[idx];
            result[i] = ((x % MOD * m) % MOD * (idx < r ? multiplier : 1)) % MOD;
        }
        return result;
    }

