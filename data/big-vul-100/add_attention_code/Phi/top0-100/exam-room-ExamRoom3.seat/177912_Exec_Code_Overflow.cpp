  tt_cmap12_validate( FT_Byte*      table,
                      FT_Validator  valid )
  {
    FT_Byte*   p;
    FT_ULong   length;
    FT_ULong   num_groups;


    if ( table + 16 > valid->limit )
      FT_INVALID_TOO_SHORT;

    p      = table + 4;
    length = TT_NEXT_ULONG( p );

    p          = table + 12;
     p          = table + 12;
     num_groups = TT_NEXT_ULONG( p );
 
    if ( table + length > valid->limit || length < 16 + 12 * num_groups )
       FT_INVALID_TOO_SHORT;
 
     /* check groups, they must be in increasing order */


      for ( n = 0; n < num_groups; n++ )
      {
        start    = TT_NEXT_ULONG( p );
        end      = TT_NEXT_ULONG( p );
        start_id = TT_NEXT_ULONG( p );

        if ( start > end )
          FT_INVALID_DATA;

        if ( n > 0 && start <= last )
          FT_INVALID_DATA;

        if ( valid->level >= FT_VALIDATE_TIGHT )
        {
          if ( start_id + end - start >= TT_VALID_GLYPH_COUNT( valid ) )
            FT_INVALID_GLYPH_ID;
        }

        last = end;
      }
    }

    int seat() {
        while (!seats_.count(max_heap_.top().first) ||
               !seats_.count(max_heap_.top().second) ||
               seats_[max_heap_.top().first].second != max_heap_.top().second ||
               seats_[max_heap_.top().second].first != max_heap_.top().first) {
            max_heap_.pop();  // lazy deletion
        }
        
        const auto top = max_heap_.top(); max_heap_.pop();
        const auto& mid = top.first == -1 ? 0
                          : top.second == num_ ? num_ - 1
                          : (top.first + top.second) / 2;
        seats_[mid] = top;
        seats_[top.first].second = mid;
        seats_[top.second].first = mid;
        max_heap_.emplace(top.first, mid);
        max_heap_.emplace(mid, top.second);
        return mid;
    }

