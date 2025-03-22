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


    bool find(const string& word, TrieNode *curr, int i, bool mistakeAllowed) {
        if (i == word.length()) {
            return curr->isString && !mistakeAllowed; 
        }

        if (!curr->leaves.count(word[i])) {
            return mistakeAllowed ?
                       any_of(curr->leaves.begin(), curr->leaves.end(),
                              [&](const pair<char, TrieNode *>& kvp) { 
                                  return find(word, kvp.second, i + 1, false);
                               }) :
                       false;
        }
                    
        if (mistakeAllowed) {
            return find(word, curr->leaves[word[i]], i + 1, true) ||
                   any_of(curr->leaves.begin(), curr->leaves.end(),
                          [&](const pair<char, TrieNode *>& kvp) { 
                              return kvp.first != word[i] && find(word, kvp.second, i + 1, false);
                          });
        }
        return find(word, curr->leaves[word[i]], i + 1, false);
    }


