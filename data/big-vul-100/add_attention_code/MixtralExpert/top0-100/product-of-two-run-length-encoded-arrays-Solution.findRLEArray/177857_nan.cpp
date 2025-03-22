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


    vector<vector<int>> findRLEArray(vector<vector<int>>& encoded1, vector<vector<int>>& encoded2) {
        vector<vector<int>> result;
        for (int i = 0, j = 0, remain1 = 0, remain2 = 0;
             (remain1 || i < size(encoded1)) && (remain2 || j < size(encoded2));) {
            if (!remain1) {
                remain1 = encoded1[i++][1];
            }
            if (!remain2) {
                remain2 = encoded2[j++][1];
            }
            int cnt = min(remain1, remain2);
            remain1 -= cnt;
            remain2 -= cnt;
            if (!empty(result) && result.back()[0] == encoded1[i - 1][0] * encoded2[j - 1][0]) {
                result.back()[1] += cnt;
            } else {
                result.push_back({encoded1[i - 1][0] * encoded2[j - 1][0], cnt});
            }
        }
        return result;
    }


