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

    vector<string> reorderLogFiles(vector<string>& logs) {
        auto pivot = stable_partition(logs.begin(), logs.end(),
                                      []( const auto& log ) {
                                          return isalpha(log.back());
                                      });
        sort(logs.begin(), pivot,
             [](const auto& a, const auto& b) {
                 int i = a.find_first_of(' '), j = b.find_first_of(' ');
                 return a.substr(i) != b.substr(j) ?
                            a.substr(i) < b.substr(j) :
                            a.substr(0, i) < b.substr(0, j);
             });
        return logs;
    }

