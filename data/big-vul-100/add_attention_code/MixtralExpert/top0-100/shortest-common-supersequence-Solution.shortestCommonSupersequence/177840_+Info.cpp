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


    string shortestCommonSupersequence(string str1, string str2) {
        vector<vector<int>> dp(2, vector<int>(str2.size() + 1));
        vector<vector<tuple<int, int, char>>> bt(str1.size() + 1,
                                                 vector<tuple<int, int, char>>(str2.size() + 1));
        for (int i = 0; i < str1.length(); ++i) {
            bt[i + 1][0] = {i, 0, str1[i]};
        }
        for (int j = 0; j < str2.length(); ++j) {
            bt[0][j + 1] = {0, j, str2[j]};
        }
        for (int i = 0; i < str1.length(); ++i) {
            for (int j = 0; j < str2.length(); ++j) {
                if (dp[i % 2][j + 1] > dp[(i + 1) % 2][j]) {
                    dp[(i + 1) % 2][j + 1] = dp[i % 2][j + 1];
                    bt[i + 1][j + 1] = {i, j + 1, str1[i]};
                } else {
                    dp[(i + 1) % 2][j + 1] = dp[(i + 1) % 2][j];
                    bt[i + 1][j + 1] = {i + 1, j, str2[j]};
                }
                if (str1[i] != str2[j]) {
                    continue;
                }
                if (dp[i % 2][j] + 1 > dp[(i + 1) % 2][j + 1]) {
                    dp[(i + 1) % 2][j + 1] = dp[i % 2][j] + 1;
                    bt[i + 1][j + 1] = {i, j, str1[i]};
                }
            }
        }
        
        int i = str1.length(), j = str2.length();
        char c = 0;
        string result;
        while (i != 0 || j != 0) {
            tie(i, j, c) = bt[i][j];
            result.push_back(c);
        }
        reverse(result.begin(), result.end());
        return result;
    }


