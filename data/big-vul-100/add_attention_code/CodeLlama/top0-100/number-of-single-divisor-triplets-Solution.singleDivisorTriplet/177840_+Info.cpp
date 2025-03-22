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


    long long singleDivisorTriplet(vector<int>& nums) {
        const auto& check = [](int a, int b, int c) {
            const int total = a + b + c;
            return (total % a == 0) + (total % b == 0) + (total % c == 0) == 1;
        };
        unordered_map<int, int64_t> cnt;
        for (const auto& x : nums) {
            ++cnt[x];
        }
        vector<int> unique_nums;
        for (const auto& [k, _] : cnt) {
            unique_nums.emplace_back(k);
        }
        int64_t result = 0;
        for (int i = 0; i < size(unique_nums); ++i) {
            for (int j = i + 1; j < size(unique_nums); ++j) {
                for (int k = j + 1; k < size(unique_nums); ++k) {
                    if (check(unique_nums[i], unique_nums[j], unique_nums[k])) {
                        result += cnt[unique_nums[i]] * cnt[unique_nums[j]] * cnt[unique_nums[k]];
                    }
                }
            }
        }
        for (int i = 0; i < size(unique_nums); ++i) {
            for (int j = 0; j < size(unique_nums); ++j) {
                if (check(unique_nums[i], unique_nums[i], unique_nums[j])) {
                    result += cnt[unique_nums[i]] * (cnt[unique_nums[i]] - 1) / 2 * cnt[unique_nums[j]];
                }
            }
        }
        return result * 6;
    }


