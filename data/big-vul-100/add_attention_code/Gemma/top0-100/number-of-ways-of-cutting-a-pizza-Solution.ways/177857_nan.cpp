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


    int ways(vector<string>& pizza, int k) {
        static int MOD = 1e9 + 7;
        vector<vector<int>> prefix(pizza.size(), vector<int>(pizza[0].size()));
        for (int j = pizza[0].size() - 1; j >= 0; --j) {
            for (int accu = 0, i = pizza.size() - 1; i >= 0; --i) {
                accu += pizza[i][j] == 'A';
                prefix[i][j] = ((j + 1 != pizza[0].size()) ? prefix[i][j + 1] : 0) + accu;
            }
        }
        vector<vector<vector<uint64_t>>> dp(pizza.size(),
                                            vector<vector<uint64_t>>(pizza[0].size(),
                                            vector<uint64_t>(k)));
        for (int i = pizza.size() - 1; i >= 0; --i) {
            for (int j = pizza[0].size() - 1; j >= 0; --j) {
                dp[i][j][0] = 1;
                for (int m = 1; m < k; ++m) {
                    for (int n = i + 1; n < pizza.size() && prefix[n][j]; ++n) {
                        if (prefix[i][j] == prefix[n][j]) {
                            continue;
                        }
                        dp[i][j][m] = (dp[i][j][m] + dp[n][j][m - 1]) % MOD;
                    }
                    for (int n = j + 1; n < pizza[0].size() && prefix[i][n]; ++n) {
                        if (prefix[i][j] == prefix[i][n]) {
                            continue;
                        }
                        dp[i][j][m] = (dp[i][j][m] + dp[i][n][m - 1]) % MOD;
                    }
                }
            }
        }
        return dp[0][0][k - 1];
    }


