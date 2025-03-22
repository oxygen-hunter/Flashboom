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

    int minOperations(vector<int>& nums) {
        static const int INF = numeric_limits<int>::max();

        const int cnt = count(cbegin(nums), cend(nums), 1);
        if (cnt) {
            return size(nums) - cnt;
        }
        int result = INF;
        for (int i = 0; i < size(nums); ++i) {
            int g = nums[i];
            for (int j = i + 1; j < size(nums); ++j) {
                g = gcd(g, nums[j]);
                if (g == 1) {
                    result = min(result, j - i);
                    break;
                }
            }
        }
        return result != INF ? result + (size(nums) - 1) : -1;
    }

