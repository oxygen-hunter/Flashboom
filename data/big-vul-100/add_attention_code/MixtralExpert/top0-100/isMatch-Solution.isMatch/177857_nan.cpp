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


        bool isMatch(const char *s, const char *p) {
            if(*p == 0) return *s == 0;

            if(*(p + 1) != '*') {
                if(*s != 0 && (*p == *s || *p == '.')) {
                    return isMatch(s + 1, p + 1);
                }
                else
                    return false;
            }
            else {
                while(*s != 0 && (*p == *s || *p == '.')) { // spanning the char
                    if(isMatch(s, p + 2))
                        return true;
                    ++s;
                }
                return isMatch(s, p + 2);
            }
        }


