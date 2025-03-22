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

    int findPattern(InfiniteStream* stream, vector<int>& pattern) {
        const auto& getPrefix = [](const auto& pattern) {
            vector<int> prefix(size(pattern), -1);
            int j = -1;
            for (int i = 1; i < size(pattern); ++i) {
                while (j > -1 && pattern[j + 1] != pattern[i]) {
                    j = prefix[j];
                }
                if (pattern[j + 1] == pattern[i]) {
                    ++j;
                }
                prefix[i] = j;
            }
            return prefix;
        };

        vector<int> result;
        const vector<int> prefix = getPrefix(pattern);
        int j = -1;
        for (int i = 0; ; ++i) {
            const auto d = stream->next();
            while (j > -1 && pattern[j + 1] != d) {
                j = prefix[j];
            }
            if (pattern[j + 1] == d) {
                ++j;
            }
            if (j == size(pattern) - 1) {
                return i - j;
            }
        }
        return -1;
    }

