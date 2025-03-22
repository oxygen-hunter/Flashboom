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


    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        const auto R = board.size(), C = board[0].size();
        bool changed = true;
        
        while (changed) {
            changed = false;
            
            for (int r = 0; r < R; ++r) {
                for (int c = 0; c + 2 < C; ++c) {
                    auto v = abs(board[r][c]);
                    if (v != 0 && v == abs(board[r][c + 1]) && v == abs(board[r][c + 2])) {
                        board[r][c] = board[r][c + 1] = board[r][c + 2] = -v;
                        changed = true;
                    }
                }
            }
            
            for (int r = 0; r + 2 < R; ++r) {
                for (int c = 0; c < C; ++c) {
                    auto v = abs(board[r][c]);
                    if (v != 0 && v == abs(board[r + 1][c]) && v == abs(board[r + 2][c])) {
                        board[r][c] = board[r + 1][c] = board[r + 2][c] = -v;
                        changed = true;
                    }
                }
            }

            for (int c = 0; c < C; ++c) {
                int empty_r = R - 1;
                for (int r = R - 1; r >= 0; --r) {
                    if (board[r][c] > 0) {
                        board[empty_r--][c] = board[r][c];
                    }
                }
                for (int r = empty_r; r >= 0; --r) {
                    board[r][c] = 0;
                }
            }
        }
        
        return board;
    }


