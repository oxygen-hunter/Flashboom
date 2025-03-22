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


    long long minimumTotalCost(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> cnt;
        int64_t result = 0;
        for (int i = 0; i < size(nums1); ++i) {
            if (nums1[i] != nums2[i]) {
                continue;
            }
            ++cnt[nums1[i]];
            result += i;
        }
        if (empty(cnt)) {
            return 0;
        }
        const int majority = max_element(cbegin(cnt), cend(cnt),
                                         [](const auto& a, const auto& b) {
                                                return a.second < b.second;
                                         })->first;
        int remain = cnt[majority] - (accumulate(cbegin(cnt), cend(cnt), 0,
                                                 [](const auto& total, const auto& x) {
                                                     return total + x.second;
                                                 }) - cnt[majority]);
        if (remain <= 0) {
            return result;
        }
        for (int i = 0; i < size(nums1); ++i) {
            if (nums1[i] == nums2[i] || nums1[i] == majority || nums2[i] == majority) {
                continue;
            }
            result += i;
            if (--remain == 0) {
                return result;
            }
        }
        return -1;
    }


