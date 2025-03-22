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


    int mergeStones(vector<int>& stones, int K) {
        if ((stones.size() - 1) % (K - 1)) {
            return -1;
        }
        vector<int> prefix(stones.size() + 1, 0);
        partial_sum(cbegin(stones), cend(stones), next(begin(prefix)), plus<int>());

        vector<vector<int> > dp(stones.size(), vector<int>(stones.size()));
        for (int l = K - 1; l < stones.size(); ++l) {
            for (int i = 0; i + l < stones.size(); ++i) {
                dp[i][i + l] = numeric_limits<int>::max();
                for (int j = i; j + 1 <= i + l; j += K - 1) {
                    dp[i][i + l] = min(dp[i][i + l], dp[i][j] + dp[j + 1][i + l]);
                }
                if (l % (K - 1) == 0) {
                    dp[i][i + l] += prefix[i + l + 1] - prefix[i];
                }
            }
        }
        return dp[0][stones.size() - 1];
    }


