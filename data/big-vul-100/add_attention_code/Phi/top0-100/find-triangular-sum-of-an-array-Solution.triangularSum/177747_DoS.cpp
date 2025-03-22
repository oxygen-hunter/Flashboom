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

    int triangularSum(vector<int>& nums) {
        const auto& exp_mod = [](const auto& p, const auto& mod) {
            vector<int> result = {p};
            while (result.back() * p % 10 != result[0]) {
                 result.emplace_back(result.back() * p %10);
            }
            rotate(rbegin(result), rbegin(result) + 1, rend(result));
            return result;
        };
        const auto& inv_mod = [](const auto& x, const auto& mod) {
            int y = x;
            while (y * x % 10 != 1) {
                y = y * x % 10;
            }
            return y;
        };
        const auto& factor_p = [](auto x, const auto& p, auto cnt, auto diff) {
            if (x == 0) {
                return make_pair(x, cnt);
            }
            while (x % p == 0) {
                x /= p;
                cnt += diff;
            }
            return make_pair(x, cnt);
        };
    
        const unordered_map<int, vector<int>> EXP = {{2, exp_mod(2, 10)}, {5, exp_mod(5, 10)}};  // {2:[6, 2, 4, 8], 5:[5]}
        const unordered_map<int, int> INV = {{1, inv_mod(1, 10)}, {3, inv_mod(3, 10)}, {7, inv_mod(7, 10)}, {9, inv_mod(9, 10)}};  // {1:1, 3:7, 7:3, 9:9}
        int result = 0;
        int nCr = 1;
        unordered_map<int, int> cnt = {{2, 0}, {5, 0}};
        for (int i = 0; i < size(nums); ++i) {
            if (!cnt[2] && !cnt[5]) {
                result = (result + nCr * nums[i]) % 10;
            } else if (cnt[2] && !cnt[5]) {
                result = (result + nCr * EXP.at(2)[cnt[2] % size(EXP.at(2))] * nums[i]) % 10;
            } else if (!cnt[2] && cnt[5]) {
                result = (result + nCr*EXP.at(5)[cnt[5] % size(EXP.at(5))] * nums[i]) % 10;
            }
            int mul = (size(nums) - 1) - i;
            tie(mul, cnt[2]) = factor_p(mul, 2, cnt[2], 1);
            tie(mul, cnt[5]) = factor_p(mul, 5, cnt[5], 1);
            int div = i + 1;
            tie(div, cnt[2]) = factor_p(div, 2, cnt[2], -1);
            tie(div, cnt[5]) = factor_p(div, 5, cnt[5], -1);
            nCr = nCr * mul % 10;
            nCr = nCr * INV.at(div % 10) % 10;
        }
        return result;
    }

