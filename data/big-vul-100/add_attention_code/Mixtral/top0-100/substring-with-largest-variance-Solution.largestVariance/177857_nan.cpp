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

    int largestVariance(string s) {
        const auto& modified_kadane = [&s](const auto& x, const auto& y) {
            int result = 0;
            vector<int> lookup(2);
            vector<int> remain = {static_cast<int>(count(cbegin(s), cend(s), x)),
                                  static_cast<int>(count(cbegin(s), cend(s), y))};
            int curr = 0;
            for (const auto& c : s) {
                if (!(c == x || c == y)) {
                    continue;
                }
                lookup[c != x] = 1;
                --remain[c != x];
                curr += (c == x) ? 1 : -1;
                if (curr < 0 && remain[0] && remain[1]) {
                    curr = lookup[0] = lookup[1] = 0;  // reset states if the remain has both x, y
                }
                if (lookup[0] && lookup[1]) {
                    result = max(result, curr);  // update result if x, y both exist
                }
            }
            return result;
        };
        
        unordered_set<char> alphabets(cbegin(s), cend(s));
        int result = 0;
        for (const auto& x : alphabets) {
            for (const auto& y: alphabets) {
                if (x != y) {
                    result = max(result, modified_kadane(x, y));
                }
            }
        }
        return result;
    }

