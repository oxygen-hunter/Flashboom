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


    string reorderSpaces(string text) {
        // count spaces and words
        int space_count = 0, word_count = 0;
        for (int i = 0; i < size(text); ++i) {
            if (text[i] == ' ') {
                ++space_count;
            } else if (i == 0 || text[i - 1] == ' ') {
                ++word_count;
            }
        }
        // rearrange the spaces to the right
        int left = 0, curr = 0;
        for (int i = 0; i < size(text); ++i) {
            bool has_word = false;
            while (i < size(text) && text[i] != ' ') {
                swap(text[left++], text[i++]);
                has_word = true;
            }
            if (has_word) {
                ++left;  // keep one space
            }
        }
        // rearrange the spaces to the left
        int equal_count = word_count - 1 > 0 ? space_count / (word_count - 1) : 0;
        int extra_count = word_count - 1 > 0 ? space_count % (word_count - 1) : space_count;
        int right = size(text) - 1 - extra_count;
        for (int i = size(text) - 1; i >= 0; --i) {
            bool has_word = false;
            while (i >= 0 && text[i] != ' ') {
                swap(text[right--], text[i--]);
                has_word = true;
            }
            if (has_word) {
                right -= equal_count;  // keep equal_count spaces
            }
        }
        return text;
    }


