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

    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
        const auto& check = [&](int i) {
            return nums[i - 1] < nums[i] && nums[i] > nums[i + 1];
        };

        BIT bit(size(nums));
        for (int i = 1; i + 1 < size(nums); ++i) {
            if (check(i)) {
                bit.add(i, +1);
            }
        }

        const auto& update = [&](int x, int d) {
            for (int i = max(x - 1, 1); i <= min(x + 1, static_cast<int>(size(nums)) - 2); ++i) {
                if (check(i)) {
                    bit.add(i, d);
                }
            }
        };

        vector<int> result;
        for (const auto& q : queries) {
            const int t = q[0], x = q[1], y = q[2];
            if (t == 1) {
                result.emplace_back(y - 1 >= x + 1 ? bit.query(y - 1) - bit.query((x + 1) - 1) : 0);
                continue;
            }
            update(x, -1);
            nums[x] = y;
            update(x, +1);
        }
        return result;
    }

