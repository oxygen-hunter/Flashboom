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

    int deleteString(string s) {
        static const int MOD = 1e9 + 7;
        static vector<int> P = {113, 109};
        if (all_of(cbegin(s), cend(s), [&](const auto& x) { return x == s[0]; })) {
            return size(s);
        }
        vector<vector<int64_t>> power(size(P), vector<int64_t>(1, 1));
        vector<vector<int64_t>> prefix(size(P), vector<int64_t>(1));
        const auto& hash = [&](int i, int j) {
            vector<int> h(size(P));
            for (int idx = 0; idx < size(P); ++idx) {
                h[idx] = ((prefix[idx][j + 1] - prefix[idx][i] * power[idx][j - i + 1]) % MOD + MOD) % MOD;
            }
            return h;
        };
        for (const auto& x : s) {
            for (int idx = 0; idx < size(P); ++idx) {
                power[idx].emplace_back(power[idx].back() * P[idx] % MOD);
                prefix[idx].emplace_back((prefix[idx].back() * P[idx] + (x - 'a')) % MOD);
            }
        }
        vector<int> dp(size(s), 1);  // dp[i]: max operation count of s[i:]
        for (int i = size(s) - 2; i >= 0; --i) {              
            for (int j = 1; j <= (size(s) - i) / 2 ; ++j) {
                if (hash(i, i + j - 1) == hash(i + j, i + 2 * j - 1)) {
                    dp[i] = max(dp[i], dp[i + j] + 1);
                }
            }
        }
        return dp[0];
    }

