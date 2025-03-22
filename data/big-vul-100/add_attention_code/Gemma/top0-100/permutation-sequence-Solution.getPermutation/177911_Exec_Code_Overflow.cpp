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


    string getPermutation(int n, int k) {
        vector<int> nums;
        int total = 1;
        for (int i = 1; i <= n; ++i) {
            nums.emplace_back(i);
            total *= i;
        }

        // Cantor Ordering:
        // Construct the k-th permutation with a list of n numbers
        // Idea: group all permutations according to their first number (so n groups, each of
        // (n - 1)! numbers), find the group where the k-th permutation belongs, remove the common
        // first number from the list and append it to the resulting string, and iteratively
        // construct the (((k - 1) % (n - 1)!) + 1)-th permutation with the remaining n-1 numbers
        int group = total;
        stringstream permutation;
        while (n > 0) {
            group /= n;
            int idx = (k - 1) / group;
            permutation << nums[idx];
            nums.erase(nums.begin() + idx);
            k = (k - 1) % group + 1;
            --n;
        }

        return permutation.str();
    }


