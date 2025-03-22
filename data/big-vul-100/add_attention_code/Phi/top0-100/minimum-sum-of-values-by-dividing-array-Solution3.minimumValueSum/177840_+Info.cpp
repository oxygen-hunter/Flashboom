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

    int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
        static const int INF = numeric_limits<int>::max();

        const auto& bit_length = [](int x) {
            return (x ? std::__lg(x) : -1) + 1;
        };

        const int FULL_MASK = (1 << bit_length(ranges::max(nums))) - 1;
        vector<vector<unordered_map<int, int>>> lookup(size(nums), vector<unordered_map<int, int>>(size(andValues)));
        const function<int (int, int, int)> memoization = [&](int i, int j, int mask) {
            if (i == size(nums) && j == size(andValues)) {
                return 0;
            }
            if (i == size(nums) || j == size(andValues) || mask < andValues[j]) {
                return INF;
            }
            if (!lookup[i][j].count(mask)) {
                int curr = memoization(i + 1, j, mask & nums[i]);
                if ((mask & nums[i]) == andValues[j]) {
                    const int total = memoization(i + 1, j + 1, FULL_MASK);
                    if (total != INF) {
                        curr = min(curr, nums[i] + total);
                    }
                }
                lookup[i][j][mask] = curr;
            }
            return lookup[i][j][mask];
        };

        const int result = memoization(0, 0, FULL_MASK);
        return result != INF ? result : -1;
    }

