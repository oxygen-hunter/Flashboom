 bgp_attr_unknown (struct bgp_attr_parser_args *args)
 {
  bgp_size_t total;
   struct transit *transit;
   struct attr_extra *attre;
   struct peer *const peer = args->peer; 
  struct attr *const attr = args->attr;
  u_char *const startp = args->startp;
  const u_char type = args->type;
  const u_char flag = args->flags;  
  const bgp_size_t length = args->length;
  

  if (BGP_DEBUG (normal, NORMAL))
  zlog_debug ("%s Unknown attribute is received (type %d, length %d)",
	      peer->host, type, length);
  
  if (BGP_DEBUG (events, EVENTS))
    zlog (peer->log, LOG_DEBUG, 
	  "Unknown attribute type %d length %d is received", type, length);

  /* Forward read pointer of input stream. */
  stream_forward_getp (peer->ibuf, length);

  /* If any of the mandatory well-known attributes are not recognized,
     then the Error Subcode is set to Unrecognized Well-known
     Attribute.  The Data field contains the unrecognized attribute
     (type, length and value). */
  if (!CHECK_FLAG (flag, BGP_ATTR_FLAG_OPTIONAL))
    {
      return bgp_attr_malformed (args,
                                 BGP_NOTIFY_UPDATE_UNREC_ATTR,
                                 args->total);
    }

  /* Unrecognized non-transitive optional attributes must be quietly
     ignored and not passed along to other BGP peers. */
  if (! CHECK_FLAG (flag, BGP_ATTR_FLAG_TRANS))
    return BGP_ATTR_PARSE_PROCEED;

  /* If a path with recognized transitive optional attribute is
     accepted and passed along to other BGP peers and the Partial bit
     in the Attribute Flags octet is set to 1 by some previous AS, it
     is not set back to 0 by the current AS. */
  SET_FLAG (*startp, BGP_ATTR_FLAG_PARTIAL);

  /* Store transitive attribute to the end of attr->transit. */
  if (! ((attre = bgp_attr_extra_get(attr))->transit) )
      attre->transit = XCALLOC (MTYPE_TRANSIT, sizeof (struct transit));

  transit = attre->transit;

  if (transit->val)
    transit->val = XREALLOC (MTYPE_TRANSIT_VAL, transit->val, 
			     transit->length + total);
  else
    transit->val = XMALLOC (MTYPE_TRANSIT_VAL, total);

  memcpy (transit->val + transit->length, startp, total);
  transit->length += total;

  return BGP_ATTR_PARSE_PROCEED;
}


    int maxMoves(int kx, int ky, vector<vector<int>>& positions) {
        static const int N = 50;
        static const vector<pair<int, int>> DIRECTIONS = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};
        static const int POS_INF = numeric_limits<int>::max();
        static const int NEG_INF = numeric_limits<int>::min();

        const auto& bfs = [](int r, int c) {
            vector<vector<int>> dist(N, vector<int>(N, POS_INF));
            dist[r][c] = 0;
            vector<pair<int, int>> q = {{r, c}};
            while (!empty(q)) {
                vector<pair<int, int>> new_q;
                for (const auto& [r, c] : q) {
                    for (const auto& [dr, dc] : DIRECTIONS) {
                        const int nr = r + dr, nc = c + dc;
                        if (!(0 <= nr && nr < N && 0 <= nc && nc < N && dist[nr][nc] == POS_INF)) {
                            continue;
                        }
                        dist[nr][nc] = dist[r][c] + 1;
                        new_q.emplace_back(nr, nc);
                    }
                }
                q = move(new_q);
            }
            return dist;
        };

        const int p = size(positions);
        positions.emplace_back(vector<int>{kx, ky});
        vector<vector<int>> dist(p + 1, vector<int>(p + 1));
        for (int i = 0; i <= p; ++i) {
            const auto& d = bfs(positions[i][0], positions[i][1]);
            for (int j = i + 1; j <= p; ++j) {
                dist[j][i] = dist[i][j] = d[positions[j][0]][positions[j][1]];
            }
        }
        vector<vector<int>> dp(1 << p);
        for (int mask = 1; mask < 1 << p; ++mask) {
            dp[mask].assign(p, __builtin_popcount(mask) & 1 ? POS_INF : NEG_INF);
        }
        dp.back().assign(p, 0);
        for (int mask = (1 << p) - 1; mask >= 1; --mask) {
            const auto& turn = (__builtin_popcount(mask) & 1) ^ 1;
            for (int i = 0; i < p; ++i) {
                if ((mask & (1 << i)) == 0) {
                    continue;
                }
                for (int j = 0; j < p; ++j) {
                    if (j == i || (mask & (1 << j)) == 0) {
                        continue;
                    }
                    dp[mask ^ (1 << i)][j] = turn ? min(dp[mask ^ (1 << i)][j], dp[mask][i] + dist[i][j])
                                                  : max(dp[mask ^ (1 << i)][j], dp[mask][i] + dist[i][j]);
                }
            }
        }
        int result = 0;
        for (int i = 0; i < p; ++i) {
            result = max(result, dp[1 << i][i] + dist[i][p]);
        }
        return result;
    }


