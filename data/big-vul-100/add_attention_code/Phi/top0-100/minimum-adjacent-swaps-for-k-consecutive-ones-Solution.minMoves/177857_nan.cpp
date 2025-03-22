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

    int minMoves(vector<int>& nums, int k) {
        vector<int> idxs;
        for (int i = 0; i < size(nums); ++i) {
            if (nums[i]) {
                idxs.emplace_back(i);
            }
        }
        vector<uint64_t> prefix(size(idxs) + 1);
        for (int i = 0; i < size(idxs); ++i) {
            prefix[i + 1] = prefix[i] + idxs[i];
        }
        const auto& score = [&prefix](int i, int j) {
                                return prefix[j + 1] - prefix[i];
                            };
        uint64_t result = numeric_limits<uint64_t>::max();
        for (int i = 0; i < size(idxs) - k + 1; ++i) {
            result = min(result, -score(i, i + k / 2 - 1) + score(i + (k + 1) / 2, i + k - 1));  // take each i+k//2 as median, find min dist to median
        }
        result -= (k / 2) * ((k + 1) / 2);  // rollback extra moves to the expected positions
        return result;
    }

