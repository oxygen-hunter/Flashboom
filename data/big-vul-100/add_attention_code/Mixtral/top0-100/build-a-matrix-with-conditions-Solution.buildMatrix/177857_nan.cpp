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

    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        const auto& topological_sort = [&](const auto& conditions) {
            vector<vector<int>> adj(k);
            vector<int> in_degree(k);
            for (const auto& c : conditions) {
                const int u = c[0] - 1, v = c[1] - 1;
                adj[u].emplace_back(v);
                ++in_degree[v];
            }
            vector<int> result;
            vector<int> q;
            for (int u = 0; u < k; ++u) {
                if (!in_degree[u]) {
                    q.emplace_back(u);
                }
            }
            while (!empty(q)) {
                vector<int> new_q;
                for (const auto& u : q) {
                    result.emplace_back(u);
                    for (const auto& v : adj[u]) {
                        --in_degree[v];
                        if (in_degree[v]) {
                            continue;
                        }
                        new_q.emplace_back(v);
                    }
                }
                q = move(new_q);
            }
            return result;
        };

        const auto& row_order = topological_sort(rowConditions);
        if (size(row_order) != k) {
            return {};
        }
        const auto& col_order = topological_sort(colConditions);
        if (size(col_order) != k) {
            return {};
        }
        vector<int> row_idx(k);
        for (int i = 0; i < k; ++i) {
            row_idx[row_order[i]] = i;
        }
        vector<int> col_idx(k);
        for (int i = 0; i < k; ++i) {
            col_idx[col_order[i]] = i;
        }
        vector<vector<int>> result(k, vector<int>(k));
        for (int i = 0; i < k; ++i) {
            result[row_idx[i]][col_idx[i]] = i + 1;
        }
        return result;
    }

