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

    int numWays(string s) {
        static const int MOD = 1e9 + 7;
        int ones = count_if(cbegin(s), cend(s),
                            [](const auto& x) {
                                return x == '1';
                            });
        if (ones % 3) {
            return 0;
        }
        ones /= 3;
        if (ones == 0) {
            return static_cast<int64_t>(s.length() - 1) * (s.length() - 2) / 2 % MOD;
        }
        int count = 0, left = 0, right = 0;
        for (const auto& c : s) {
            if (c == '1') {
                ++count;
            }
            if (count == ones) {
                ++left;
            } else if (count == 2 * ones) {
                ++right;
            }
        }
        return static_cast<int64_t>(left) * right % MOD;
    }

