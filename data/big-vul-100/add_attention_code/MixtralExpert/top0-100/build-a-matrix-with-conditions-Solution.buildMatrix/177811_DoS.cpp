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


    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        const auto& topological_sort = [&](const auto& conditions) {
            vector<vector<int>> adj(k);
            vector<int> in_degree(k);
            for (const auto& c : conditions) {
                const int u = c[0] - 1, v = c[1] - 1;
                adj[u].emplace_back(v);
                ++in_degree[v];
            }
            vector<int> result;
            vector<int> q;
            for (int u = 0; u < k; ++u) {
                if (!in_degree[u]) {
                    q.emplace_back(u);
                }
            }
            while (!empty(q)) {
                vector<int> new_q;
                for (const auto& u : q) {
                    result.emplace_back(u);
                    for (const auto& v : adj[u]) {
                        --in_degree[v];
                        if (in_degree[v]) {
                            continue;
                        }
                        new_q.emplace_back(v);
                    }
                }
                q = move(new_q);
            }
            return result;
        };

        const auto& row_order = topological_sort(rowConditions);
        if (size(row_order) != k) {
            return {};
        }
        const auto& col_order = topological_sort(colConditions);
        if (size(col_order) != k) {
            return {};
        }
        vector<int> row_idx(k);
        for (int i = 0; i < k; ++i) {
            row_idx[row_order[i]] = i;
        }
        vector<int> col_idx(k);
        for (int i = 0; i < k; ++i) {
            col_idx[col_order[i]] = i;
        }
        vector<vector<int>> result(k, vector<int>(k));
        for (int i = 0; i < k; ++i) {
            result[row_idx[i]][col_idx[i]] = i + 1;
        }
        return result;
    }


