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

    int minimumOperations(vector<int>& nums, int start, int goal) {
        static const int MAX_X = 1000;

        vector<int> new_nums;
        for (const auto& y : nums) {
            if (y && ((0 <= y && y <= MAX_X) || (0 <= (goal - y) && (goal - y) <= MAX_X) || (0 <= (goal + y) && (goal + y) <= MAX_X) || (0 <= (goal ^ y) && (goal ^ y) <= MAX_X))) {
                new_nums.emplace_back(y);
            }
        }
        nums = move(new_nums);
        vector<pair<int, int>> q = {{start, 0}};
        unordered_set<int> lookup = {start};
        while (!empty(q)) {
            vector<pair<int, int>> new_q;
            for (const auto& [x, steps] : q) {
                for (const auto& y : nums) {
                    for (const auto& nx : {x + y, x - y, x ^ y}) {
                        if (nx == goal) {
                            return steps + 1;
                        }
                        if (!(0 <= nx && nx <= MAX_X) || lookup.count(nx)) {
                            continue;
                        }
                        lookup.emplace(nx);
                        new_q.emplace_back(nx, steps + 1);
                    }
                }
            }
            q = move(new_q);
        }
        return -1;
    }

