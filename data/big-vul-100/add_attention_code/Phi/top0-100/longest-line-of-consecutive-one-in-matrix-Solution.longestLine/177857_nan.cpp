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

    int longestLine(vector<vector<int>>& M) {
        if (M.empty()) {
            return 0;
        }
        int result = 0;
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(M[0].size(), vector<int>(4)));
        for (int i = 0; i < M.size(); ++i) {
            for (int j = 0; j < M[0].size(); ++j) {
                dp[i % 2][j][0] = dp[i % 2][j][1] = dp[i % 2][j][2] = dp[i % 2][j][3] = 0;
                if (M[i][j] == 1) {
                    dp[i % 2][j][0] = j > 0 ? dp[i % 2][j - 1][0] + 1 : 1;
                    dp[i % 2][j][1] = i > 0 ? dp[(i - 1) % 2][j][1] + 1 : 1;
                    dp[i % 2][j][2] = (i > 0 && j > 0) ? dp[(i - 1) % 2][j - 1][2] + 1 : 1;
                    dp[i % 2][j][3] = (i > 0 && j < M[0].size() - 1) ? dp[(i - 1) % 2][j + 1][3] + 1 : 1;
                    result = max(result, max(dp[i % 2][j][0], max(dp[i % 2][j][1], max(dp[i % 2][j][2], dp[i % 2][j][3]))));
                }
            }
        }
        return result;
    }

