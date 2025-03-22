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


    bool wordPattern(string pattern, string str) {
        // Count the words.
        int cnt = str.empty() ? 0 : 1;
        for (const auto& c : str) {
            if (c == ' ') {
                ++cnt;
            }
        }
        if (pattern.size() != cnt) {
            return false;
        }

        unordered_map<string, char> w2p;
        unordered_map<char, string> p2w;
        int i = 0, j = 0;
        for (const auto& p : pattern) {
            // Get a word at a time without saving all the words.
            j = str.find(" ", i);
            if (j == string::npos) {
                j = str.length();
            }
            const string w = str.substr(i, j - i);
    
            if (!w2p.count(w) && !p2w.count(p)) { 
                // Build mapping. Space: O(c)
                w2p[w] = p; 
                p2w[p] = w; 
            } else if (!w2p.count(w) || w2p[w] != p) {
                // Contradict mapping.
                return false;
            }
            i = j + 1;
        }
        return true;
    }


