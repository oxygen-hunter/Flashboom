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


    long long singleDivisorTriplet(vector<int>& nums) {
        const auto& check = [](int a, int b, int c) {
            const int total = a + b + c;
            return (total % a == 0) + (total % b == 0) + (total % c == 0) == 1;
        };
        unordered_map<int, int64_t> cnt;
        for (const auto& x : nums) {
            ++cnt[x];
        }
        vector<int> unique_nums;
        for (const auto& [k, _] : cnt) {
            unique_nums.emplace_back(k);
        }
        int64_t result = 0;
        for (int i = 0; i < size(unique_nums); ++i) {
            for (int j = i + 1; j < size(unique_nums); ++j) {
                for (int k = j + 1; k < size(unique_nums); ++k) {
                    if (check(unique_nums[i], unique_nums[j], unique_nums[k])) {
                        result += cnt[unique_nums[i]] * cnt[unique_nums[j]] * cnt[unique_nums[k]];
                    }
                }
            }
        }
        for (int i = 0; i < size(unique_nums); ++i) {
            for (int j = 0; j < size(unique_nums); ++j) {
                if (check(unique_nums[i], unique_nums[i], unique_nums[j])) {
                    result += cnt[unique_nums[i]] * (cnt[unique_nums[i]] - 1) / 2 * cnt[unique_nums[j]];
                }
            }
        }
        return result * 6;
    }


