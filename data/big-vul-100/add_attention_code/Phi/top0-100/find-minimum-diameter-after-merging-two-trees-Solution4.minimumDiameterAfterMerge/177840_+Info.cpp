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

    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        const auto& ceil_divide = [](const auto& a, const auto& b) {
            return (a + b - 1) / 2;
        };

        const auto& tree_diameter = [](const auto& edges) {
            vector<vector<int>> adj(size(edges) + 1);
            for (const auto& e : edges) {
                adj[e[0]].emplace_back(e[1]);
                adj[e[1]].emplace_back(e[0]);
            }
            int result = 0;
            const auto& bfs = [&](int root) {
                int d = -1, new_root = -1;
                vector<bool> lookup(size(adj));
                lookup[root] = true;
                vector<int> q = {root};
                while (!empty(q)) {
                    ++d;
                    new_root = q[0];
                    vector<int> new_q;
                    for (const auto& u : q) {
                        for (const auto& v : adj[u]) {
                            if (lookup[v]) {
                                continue;
                            }
                            lookup[v] = true;
                            new_q.emplace_back(v);
                        }
                    }
                    q = move(new_q);
                }
                return pair(d, new_root);
            };

            const auto& [_, root] = bfs(0);
            const auto& [d, __] = bfs(root);
            return d;
        };

        const int d1 = tree_diameter(edges1);
        const int d2 = tree_diameter(edges2);
        return max({ceil_divide(d1, 2) + 1 + ceil_divide(d2, 2), d1, d2});
    }

