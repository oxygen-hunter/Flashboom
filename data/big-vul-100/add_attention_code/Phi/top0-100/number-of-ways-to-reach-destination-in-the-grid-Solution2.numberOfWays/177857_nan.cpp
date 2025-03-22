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

    int numberOfWays(int n, int m, int k, vector<int>& source, vector<int>& dest) {
        static const int MOD = 1e9 + 7;
    
        int both_same = 0, row_same = 0, col_same = 0, no_same = 0;
        if (source == dest) {
            both_same = 1;
        } else if (source[0] == dest[0]) {
            row_same = 1;
        } else if (source[1] == dest[1]) {
            col_same = 1;
        } else {
            no_same = 1;
        }
        for (int _ = 0; _ < k; ++_) {
            tie(both_same, row_same, col_same, no_same) = tuple(
                (row_same + col_same) % MOD,
                (both_same * static_cast<int64_t>(m - 1) + row_same * static_cast<int64_t>(m - 2) + no_same) % MOD,
                (both_same * static_cast<int64_t>(n - 1) + col_same * static_cast<int64_t>(n - 2) + no_same) % MOD,
                (row_same * static_cast<int64_t>(n - 1) + col_same * static_cast<int64_t>(m - 1) + no_same * static_cast<int64_t>((n - 2) + (m - 2))) % MOD
            );
        }
        return both_same;
    }

