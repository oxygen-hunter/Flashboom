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


    int minMoves(vector<int>& nums, int k) {
        vector<int> idxs;
        for (int i = 0; i < size(nums); ++i) {
            if (nums[i]) {
                idxs.emplace_back(i);
            }
        }
        vector<uint64_t> prefix(size(idxs) + 1);
        for (int i = 0; i < size(idxs); ++i) {
            prefix[i + 1] = prefix[i] + idxs[i];
        }
        const auto& score = [&prefix](int i, int j) {
                                return prefix[j + 1] - prefix[i];
                            };
        uint64_t result = numeric_limits<uint64_t>::max();
        for (int i = 0; i < size(idxs) - k + 1; ++i) {
            result = min(result, -score(i, i + k / 2 - 1) + score(i + (k + 1) / 2, i + k - 1));  // take each i+k//2 as median, find min dist to median
        }
        result -= (k / 2) * ((k + 1) / 2);  // rollback extra moves to the expected positions
        return result;
    }


