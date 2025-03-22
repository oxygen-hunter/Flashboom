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


    vector<vector<int>> highestRankedKItems(vector<vector<int>>& grid, vector<int>& pricing, vector<int>& start, int k) {
        static const vector<pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        vector<pair<int, int>> q = {{start[0], start[1]}};
        vector<vector<int>> lookup(size(grid), vector<int>(size(grid[0]), -1));
        int d = lookup[start[0]][start[1]] = 0;
        auto compare = [&](const auto& x, const auto& y) {
            return make_tuple(lookup[x[0]][x[1]], grid[x[0]][x[1]], x[0], x[1]) <
                   make_tuple(lookup[y[0]][y[1]], grid[y[0]][y[1]], y[0], y[1]);
        };
        vector<vector<int>> result;
        while (!empty(q)) {
            if (size(result) >= k) {
                if (size(result) > k) {
                    nth_element(begin(result), begin(result) + k, end(result), compare);
                    result.resize(k);
                }
                break;
            }
            vector<pair<int, int>> new_q;
            for (const auto& [r, c] : q) {
                if (pricing[0] <= grid[r][c] && grid[r][c] <= pricing[1]) {
                    result.push_back({r, c});
                }
                for (const auto& [dr, dc] : directions) {
                    const int nr = r + dr, nc = c + dc;
                    if (!((0 <= nr && nr < size(grid)) && (0 <= nc && nc < size(grid[0])) &&
                           grid[nr][nc] && lookup[nr][nc] == -1)) {
                        continue;
                    }
                    lookup[nr][nc] = d + 1;
                    new_q.emplace_back(nr, nc);
                }
            }
            q = move(new_q);
            ++d;
        }
        sort(begin(result), end(result), compare);
        return result;
    }


