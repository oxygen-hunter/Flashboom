plan_a (char const *filename)
{
  char const *s;
  char const *lim;
  char const **ptr;
  char *buffer;
  lin iline;
  size_t size = instat.st_size;

  /* Fail if the file size doesn't fit in a size_t,
     or if storage isn't available.  */
  if (! (size == instat.st_size
	 && (buffer = malloc (size ? size : (size_t) 1))))
    return false;

  /* Read the input file, but don't bother reading it if it's empty.
     When creating files, the files do not actually exist.  */
  if (size)
     {
       if (S_ISREG (instat.st_mode))
         {
	  int ifd = safe_open (filename, O_RDONLY|binary_transput, 0);
 	  size_t buffered = 0, n;
 	  if (ifd < 0)
 	    pfatal ("can't open file %s", quotearg (filename));
 
		  /* Some non-POSIX hosts exaggerate st_size in text mode;
		     or the file may have shrunk!  */
		  size = buffered;
		  break;
		}
	      if (n == (size_t) -1)
		{
		  /* Perhaps size is too large for this host.  */
		  close (ifd);
		  free (buffer);
		  return false;
		}
	      buffered += n;
	    }

	  if (close (ifd) != 0)
	    read_fatal ();
	}


    int countWinningSequences(string s) {
        static const int MOD = 1e9 + 7;
        static const unordered_map<char, int> lookup = {{'F', 0}, {'W', 1}, {'E', 2}};

        vector<unordered_map<int, int>> dp(3);
        for (int i = 0; i < size(s); ++i) {
            vector<unordered_map<int, int>> new_dp(3);
            const auto x = lookup.at(s[i]);
            for (int j = 0; j < 3; ++j) {
                const int diff = ((j - x + 1) % 3 + 3) % 3 - 1;
                if (i == 0) {
                    new_dp[j][diff] = 1;
                    continue;
                }
                for (int k = 0; k < 3; ++k) {
                    if (k == j) {
                        continue;
                    }
                    for (const auto& [v, c] : dp[k]) {
                        new_dp[j][v + diff] = (new_dp[j][v + diff] + c) % MOD;
                    }
                }
            }
            dp = move(new_dp);
        }
        int result = 0;
        for (int j = 0; j < 3; ++j) {
            for (const auto& [v, c] : dp[j]) {
                if (v >= 1) {
                    result = (result + c) % MOD;
                }
            }
        }
        return result;
    }


