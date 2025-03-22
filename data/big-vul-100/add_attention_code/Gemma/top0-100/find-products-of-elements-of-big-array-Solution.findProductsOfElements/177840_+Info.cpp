 static int ldb_dn_escape_internal(char *dst, const char *src, int len)
 {
       const char *p, *s;
        char *d;
       size_t l;
       p = s = src;
        d = dst;
 
       while (p - src < len) {
               p += strcspn(p, ",=\n\r+<>#;\\\" ");
               if (p - src == len) /* found no escapable chars */
                       break;
               /* copy the part of the string before the stop */
               memcpy(d, s, p - s);
               d += (p - s); /* move to current position */
               switch (*p) {
                case ' ':
                       if (p == src || (p-src)==(len-1)) {
                                /* if at the beginning or end
                                 * of the string then escape */
                                *d++ = '\\';
                               *d++ = *p++;                                     
                        } else {
                                /* otherwise don't escape */
                               *d++ = *p++;
                        }
                        break;
 
				/* if at the beginning or end
				 * of the string then escape */
				*d++ = '\\';
				*d++ = *p++;					 
			} else {
				/* otherwise don't escape */
				*d++ = *p++;
			}
			break;
                case '?':
                        /* these must be escaped using \c form */
                        *d++ = '\\';
                       *d++ = *p++;
                        break;
 
               default: {
                        /* any others get \XX form */
                        unsigned char v;
                        const char *hexbytes = "0123456789ABCDEF";
                       v = *(const unsigned char *)p;
                        *d++ = '\\';
                        *d++ = hexbytes[v>>4];
                        *d++ = hexbytes[v&0xF];
                       p++;
                        break;
                }
                }
               s = p; /* move forward */
        }


    vector<int> findProductsOfElements(vector<vector<long long>>& queries) {
        const auto& binary_search = [](auto left, auto right, const auto& check) {
            while (left <= right) {
                const auto mid = left + ((right - left) / 2);
                if (check(mid)) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return left;
        };

        const auto& powmod = [&](auto a, auto b, int mod) {
            a %= mod;
            auto result = 1 % mod;
            while (b) {
                if (b & 1) {
                    result = result * a % mod;
                }
                a = a * a % mod;
                b >>= 1;
            }
            return result;
        };

        const auto& count1 = [&](auto x) {
            auto result = 0ll;
            for (int i = 0; (1ll << i) <= x; ++i) {
                const auto mask = (1ll << (i + 1)) - 1;
                result += ((x & ~mask) >> 1) + max((x & mask) - (1ll << i) + 1, 0ll);
            }
            return result;
        };
        
        const auto& count2 = [&](auto x) {
            auto result = 0ll;
            for (int i = 0; (1ll << i) <= x; ++i) {
                const auto mask = (1ll << (i + 1)) - 1;
                result += (((x & ~mask) >> 1) + max((x & mask) - (1ll << i) + 1, 0ll)) * i;
            }
            return result;
        };
    
        const auto& f = [&](auto x) {
            const auto y = binary_search(1ll, x - 1, [&](auto i) {
                return count1(i) >= x;
            });
            auto result = count2(y - 1);
            x -= count1(y - 1);
            for (int i = 0; (1ll << i) <= y; ++i) {
                if ((y & (1ll << i)) == 0) {
                    continue;
                }
                result += i;
                if (--x == 0) {
                    break;
                }
            }
            return result;
        };
    
        vector<int> result(size(queries));
        for (int i = 0; i < size(queries); ++i) {
            const auto left = queries[i][0], right = queries[i][1], mod = queries[i][2];
            result[i] =  powmod(2ll, f(right + 1) - f(left), mod);
        }
        return result;
    }


