aspath_put (struct stream *s, struct aspath *as, int use32bit )
{
  struct assegment *seg = as->segments;
  size_t bytes = 0;
  
  if (!seg || seg->length == 0)
    return 0;
  
  if (seg)
    {
      /*
       * Hey, what do we do when we have > STREAM_WRITABLE(s) here?
       * At the moment, we would write out a partial aspath, and our peer
       * will complain and drop the session :-/
       *
       * The general assumption here is that many things tested will
       * never happen.  And, in real live, up to now, they have not.
       */
      while (seg && (ASSEGMENT_LEN(seg, use32bit) <= STREAM_WRITEABLE(s)))
        {
          struct assegment *next = seg->next;
          int written = 0;
          int asns_packed = 0;
          size_t lenp;
          
          /* Overlength segments have to be split up */
          while ( (seg->length - written) > AS_SEGMENT_MAX)
            {
               assegment_header_put (s, seg->type, AS_SEGMENT_MAX);
               assegment_data_put (s, seg->as, AS_SEGMENT_MAX, use32bit);
               written += AS_SEGMENT_MAX;
              bytes += ASSEGMENT_SIZE (written, use32bit);
             }
           
           /* write the final segment, probably is also the first */
          lenp = assegment_header_put (s, seg->type, seg->length - written);
          assegment_data_put (s, (seg->as + written), seg->length - written, 
                              use32bit);
          
          /* Sequence-type segments can be 'packed' together
           * Case of a segment which was overlength and split up
           * will be missed here, but that doesn't matter.
           */
          while (next && ASSEGMENTS_PACKABLE (seg, next))
            {
              /* NB: We should never normally get here given we
               * normalise aspath data when parse them. However, better
               * safe than sorry. We potentially could call
               * assegment_normalise here instead, but it's cheaper and
               * easier to do it on the fly here rather than go through
               * the segment list twice every time we write out
               * aspath's.
               */
              
              /* Next segment's data can fit in this one */
              assegment_data_put (s, next->as, next->length, use32bit);
              
              /* update the length of the segment header */
	      stream_putc_at (s, lenp, seg->length - written + next->length);
              asns_packed += next->length;
               
	      next = next->next;
	    }
          
          bytes += ASSEGMENT_SIZE (seg->length - written + asns_packed, 
				   use32bit);
          seg = next;
        }
    }
  return bytes;
}

    int palindromePartition(string s, int k) {
        // dp1[i][j]: minimum number of changes to make s[i, j] palindrome
        vector<vector<int>> dp1(s.length(), vector<int>(s.length()));
        for (int l = 1; l <= s.length(); ++l) {
            for (int i = 0; i + l <= s.length(); ++i) {
                int j = i + l - 1;
                if (i == j - 1) {
                    dp1[i][j] = s[i] == s[j] ? 0 : 1;
                }  else if (i != j) {
                    dp1[i][j] = s[i] == s[j] ? dp1[i + 1][j - 1] : dp1[i + 1][j - 1] + 1;
                }
            }
        }
        // dp2[d][i]: minimum number of changes to divide s[0, i] into d palindromes
        vector<vector<int>> dp2(2, vector<int>(s.length(), numeric_limits<int>::max()));
        dp2[1] = dp1[0];
        for (int d = 2; d <= k; ++d) {
            dp2[d % 2] = vector<int>(s.length(), numeric_limits<int>::max());
            for (int i = d - 1; i < s.length(); ++i) {
                for (int j = d - 2; j < i; ++j) {
                    dp2[d % 2][i] = min(dp2[d % 2][i], dp2[(d - 1) % 2][j] + dp1[j + 1][i]);
                }
            }
        }
        return dp2[k % 2][s.length() - 1];
    }

