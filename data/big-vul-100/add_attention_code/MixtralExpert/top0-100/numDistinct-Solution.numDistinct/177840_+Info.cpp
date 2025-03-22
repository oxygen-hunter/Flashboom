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


        int numDistinct(const string &S, const string &T) {
            vector<int> f(T.size() + 1);
            f[0] = 1; // f(0, 0) = 1, means S = "" and T = "", there is only one distinct subsequence, i.e. ""
            for (int i = 1; i <= S.size(); ++i) {
                for (int j = T.size(); j > 0; --j) {
                    // f(i, j) is composed of:
                    // f(i−1,j): not using S[i - 1] 
                    // f(i−1,j−1): using S[i - 1] if S[i - 1] == S[j - 1]
                    f[j] += (S[i - 1] == T[j - 1]) ? f[j - 1] : 0;
                }
            }
            return f[T.size()];
        }


