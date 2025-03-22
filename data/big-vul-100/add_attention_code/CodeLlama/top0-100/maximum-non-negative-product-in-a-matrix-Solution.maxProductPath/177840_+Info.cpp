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


    int maxProductPath(vector<vector<int>>& grid) {
        static const int MOD = 1e9 + 7;
        vector<vector<int64_t>> max_dp(2, vector<int64_t>(size(grid[0])));
        vector<vector<int64_t>> min_dp(2, vector<int64_t>(size(grid[0])));
        for (int i = 0; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]); ++j) {
                if (i == 0 && j == 0) {
                    max_dp[0][0] = min_dp[0][0] = grid[0][0];
                    continue;
                }
                auto curr_max = max(i > 0 ? max_dp[(i - 1) % 2][j] : max_dp[i % 2][j - 1],
                                    j > 0 ? max_dp[i % 2][j - 1] : max_dp[(i - 1) % 2][j]);
                auto curr_min = min(i > 0 ? min_dp[(i - 1) % 2][j] : min_dp[i % 2][j - 1],
                                    j > 0 ? min_dp[i % 2][j - 1] : min_dp[(i - 1) % 2][j]);
                if (grid[i][j] < 0) {
                    swap(curr_max, curr_min);
                }
                max_dp[i % 2][j] = curr_max * grid[i][j];
                min_dp[i % 2][j] = curr_min * grid[i][j];
            }
        }
        return max_dp[(size(grid) - 1) % 2].back() >= 0 ? max_dp[(size(grid) - 1) % 2].back() % MOD : -1;
    }


