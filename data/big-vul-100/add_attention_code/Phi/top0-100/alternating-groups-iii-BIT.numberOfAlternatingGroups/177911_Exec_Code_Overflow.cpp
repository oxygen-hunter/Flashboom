  tt_cmap10_validate( FT_Byte*      table,
                      FT_Validator  valid )
  {
    FT_Byte*  p = table + 4;
    FT_ULong  length, count;


    if ( table + 20 > valid->limit )
      FT_INVALID_TOO_SHORT;

    length = TT_NEXT_ULONG( p );
     p      = table + 16;
     count  = TT_NEXT_ULONG( p );
 
    if ( table + length > valid->limit || length < 20 + count * 2 )
       FT_INVALID_TOO_SHORT;
 
     /* check glyph indices */
    {
      FT_UInt  gindex;


      for ( ; count > 0; count-- )
      {
        gindex = TT_NEXT_USHORT( p );
        if ( gindex >= TT_VALID_GLYPH_COUNT( valid ) )
          FT_INVALID_GLYPH_ID;
      }
    }

    return SFNT_Err_Ok;
  }

    vector<int> numberOfAlternatingGroups(vector<int>& colors, vector<vector<int>>& queries) {
        const int n = size(colors);
        set<int> bst;
        BIT bit1(n + 1), bit2(n + 1);
        const auto& update = [&](int i, int d) {
            if (d == +1) {
                bst.emplace(i);
                if (size(bst) == 1) {
                    bit1.add(n, +1);
                    bit2.add(n, +n);
                }
            }
            auto curr = bst.find(i);
            auto prv = prev(curr != begin(bst) ? curr : end(bst));
            auto nxt = next(curr);
            if (nxt == end(bst)) {
                nxt = begin(bst);
            }
            if (size(bst) != 1) {
                int l = ((*nxt) - (*prv) + (n - 1)) % n + 1;
                bit1.add(l, d * -1);
                bit2.add(l, d * -l);
                l = ((*curr) - (*prv) + n) % n;
                bit1.add(l, d * +1);
                bit2.add(l, d * +l);
                l = ((*nxt) - (*curr) + n) % n;
                bit1.add(l, d * +1);
                bit2.add(l, d * +l);
            }
            if (d == -1) {
                if (size(bst) == 1) {
                    bit1.add(n, -1);
                    bit2.add(n, -n);
                }
                bst.erase(curr);
            }
        };

        vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (colors[i] == colors[(i + 1) % n]) {
                update(i, +1);
            }
        }
        for (const auto &q : queries) {
            if (q[0] == 1) {
                const int l = q[1];
                result.emplace_back(!empty(bst) ? (bit2.query(n) - bit2.query(l - 1)) - 
                                                  (l - 1) * (bit1.query(n) - bit1.query(l - 1)) : n);
                continue;
            }
            const int i = q[1];
            if (colors[i] == q[2]) {
                continue;
            }
            colors[i] = q[2];
            update((i - 1 + n) % n, colors[i] == colors[(i - 1 + n) % n] ? +1 : -1);
            update(i, colors[i] == colors[(i + 1) % n] ? +1 : -1);
        }
        return result;
    }

