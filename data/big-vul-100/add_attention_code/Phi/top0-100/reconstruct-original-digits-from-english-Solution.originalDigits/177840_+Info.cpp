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

    string originalDigits(string s) {
        const vector<string> numbers{"zero", "one", "two", "three",
                                     "four", "five", "six", "seven",
                                     "eight", "nine"};
        vector<vector<int>> cnts(numbers.size(), vector<int>(26));
        for (int i = 0; i < numbers.size(); ++i) {
            for (const auto& c : numbers[i]) {
                ++cnts[i][c - 'a'];
            }
        }
        
        // The order for greedy method.
        vector<int> order{0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
        
        // The unique char in the order.
        vector<char> unique_chars{'z', 'o', 'w', 't', 'u', 'f', 'x', 's', 'g', 'n'};
        vector<int> cnt(26);
        for (const auto& c : s) {
            ++cnt[c - 'a'];
        }

        string result;
        for (const auto& i : order) {
            while (cnt[unique_chars[i] - 'a'] > 0) {
                for (int j = 0; j < cnt.size(); ++j) {
                    cnt[j] -= cnts[i][j];
                }
                result.push_back(i + '0');
            }
        }
        sort(result.begin(), result.end());
        return result;
    }

