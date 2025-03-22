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

    vector<vector<int>> outerTrees(vector<vector<int>>& P) {
        // 3D cross product of OA and OB vectors, (i.e z-component of their "2D" cross product, but remember that it is not defined in "2D").
        // Returns a positive value, if OAB makes a counter-clockwise turn,
        // negative for clockwise turn, and zero if the points are collinear.
        const auto& cross = [](const vector<int>& O, const vector<int>& A, const vector<int>& B) {
            return (A[0] - O[0]) * (B[1] - O[1]) - (A[1] - O[1]) * (B[0] - O[0]);
        };

        // Returns a list of points on the convex hull in counter-clockwise order.
        // Note: the last point in the returned list is the same as the first one.
        size_t n = P.size(), k = 0;
        if (n <= 3) {
            return P;
        }
        vector<vector<int>> H(2*n);

        // Sort points lexicographically
        sort(P.begin(), P.end());

        // Build lower hull
        for (size_t i = 0; i < n; ++i) {
            while (k >= 2 && cross(H[k-2], H[k-1], P[i]) < 0) k--; // modified
            H[k++] = P[i];
        }

        // Build upper hull
        for (size_t i = n-1, t = k+1; i > 0; --i) {
            while (k >= t && cross(H[k-2], H[k-1], P[i-1]) < 0) k--; // modified
            H[k++] = P[i-1];
        }

        H.resize(--k);        
        if (H[1] == H[k - 1]) {  // modified
            H.resize(k / 2 + 1);
        }
        return H;
    }

