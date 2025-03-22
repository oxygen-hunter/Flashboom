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


    int minSwapsCouples(vector<int>& row) {
        int N = row.size() / 2;
        vector<vector<int>> couples(N);
        for (int seat = 0; seat < row.size(); ++seat) {
            couples[row[seat] / 2].emplace_back(seat / 2);
        }
        vector<vector<int>> adj(N);
        for (const auto& couple : couples) {
            adj[couple[0]].emplace_back(couple[1]);
            adj[couple[1]].emplace_back(couple[0]);
        }
        
        int result = 0;
        for (int couch = 0; couch < N; ++couch) {
            if (adj[couch].empty()) {
                continue;
            }
            int couch1 = couch;
            int couch2 = adj[couch1].back(); adj[couch1].pop_back();
            while (couch2 != couch) {
                ++result;
                adj[couch2].erase(find(adj[couch2].begin(), adj[couch2].end(), couch1));
                couch1 = couch2;
                couch2 = adj[couch1].back(); adj[couch1].pop_back();
            }
        }
        return result;  // also equals to N - (# of cycles)
    }


