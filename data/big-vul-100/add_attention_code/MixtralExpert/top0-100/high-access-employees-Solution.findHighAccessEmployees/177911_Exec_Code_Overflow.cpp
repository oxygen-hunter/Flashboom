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


    vector<string> findHighAccessEmployees(vector<vector<string>>& access_times) {
        static const int LIMIT_COUNT = 2;
        static const int LIMIT_MINUTE = 60;
    
        const auto& to_minute = [](const auto& s) {
            return stoi(s.substr(0, 2)) * 60 + stoi(s.substr(2));
        };
    
        unordered_map<string, vector<int>> lookup;;
        for (const auto& x : access_times) {
            lookup[x[0]].emplace_back(to_minute(x[1]));
        }
        vector<string> result;
        for (auto& [x, ts] : lookup) {
            sort(begin(ts), end(ts));
            for (int i = 0; i + LIMIT_COUNT < size(ts); ++i) {
                if (!(ts[i] + LIMIT_MINUTE <= ts[i + LIMIT_COUNT])) {
                    result.emplace_back(x);
                    break;
                }
            } 
        }
        return result;
    }


