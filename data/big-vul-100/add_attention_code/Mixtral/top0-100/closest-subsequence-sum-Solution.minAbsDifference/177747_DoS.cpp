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

    int minAbsDifference(vector<int>& nums, int goal) {
        int mx = 0, mn = 0;
        for (const auto& x : nums) {
            if (x > 0) {
                mx += x;
            } else if (x < 0) {
                mn += x;
            }
        }
        if (goal > mx) {
            return goal - mx;
        }
        if (goal < mn) {
            return mn - goal;
        }
        int result = abs(goal);
        unordered_set<int> sums1{0};
        for (auto i = 0; i < size(nums) / 2; ++i) {
            for (const auto& x : vector<int>(cbegin(sums1), cend(sums1))) {
                if (!sums1.emplace(x + nums[i]).second) {
                    continue;
                }
                result = min(result, abs(goal - x - nums[i]));  // case of right half part is 0
            }
        }
        vector<int> sorted_sums1(cbegin(sums1), cend(sums1));  // Space: O(2^(n/2))
        sort(begin(sorted_sums1), end(sorted_sums1));  // Time: O((n/2) * 2^(n/2)) = O(n * 2^(n/2))
        unordered_set<int> sums2{0};
        for (int i = size(nums) / 2; i < size(nums); ++i) {
            for (const auto& x : vector<int>(cbegin(sums2), cend(sums2))) {
                if (!sums2.emplace(x + nums[i]).second) {
                    continue;
                }
                auto cit = lower_bound(cbegin(sorted_sums1), cend(sorted_sums1), goal - x - nums[i]);  // Time: O(2^(n/2)) * O(n/2)
                if (cit != cend(sorted_sums1)) {
                    result = min(result, abs(goal - x - nums[i] - *cit));
                }
                if (cit != cbegin(sorted_sums1)) {
                    result = min(result, abs(goal - x - nums[i] - *prev(cit)));
                }
                if (result == 0) {
                    return result;
                }
            }
        }
        return result;
    }

