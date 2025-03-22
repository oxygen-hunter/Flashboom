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

    string largestPalindrome(int n, int k) {
        const auto& powmod = [](uint32_t a, uint32_t b, uint32_t mod) {
            a %= mod;
            uint64_t result = 1;
            while (b) {
                if (b & 1) {
                    result = result * a % mod;
                }
                a = uint64_t(a) * a % mod;
                b >>= 1;
            }
            return result;
        };

        const auto& inv = [&](int x, int p) {
            return powmod(x, p - 2, p);
        };

        const auto& f = [&](int l) {
            static const int p = 7;
            string result(l, '9');
            if (l == 0) {
                return result;
            }
            int curr = 0;
            for (const auto& x : result) {
                curr = (curr * 10 + (x - '0')) % p;
            }
            // l%2 == 0: (curr+(i-9)*11*pow(10, l//2-1, p))%p = 0
            // l%2 == 1: (curr+(i-9)*pow(10, l//2, p))%p = 0
            int i = 9 - (curr * inv(l % 2 == 0 ? 11 : 1, p) * inv(powmod(10, l / 2 - (l % 2 == 0 ? 1 : 0), p), p)) % p;
            if (i <= 2) {
                i += p;
            }
            result[l / 2] = result[l / 2 - (l % 2 == 0 ? 1 : 0)] = '0' + i;
            return result;
        };

        if (k == 1 || k == 3 || k == 9) {
            return string(n, '9');
        }
        if (k == 2 || k == 4 || k == 8) {
            k = min(k, 6);
            if (n <= k) {
                return string(n, '8');
            }
            const int l = k / 2;
            return string(l, '8') + string(n - k, '9') + string(l, '8');
        }
        if (k == 5) {
            if (n <= 2) {
                return string(n, '5');
            }
            return string(1, '5') + string(n - 2, '9') + string(1, '5');
        }
        if (k == 6) {
            if (n <= 2) {
                return string(n, '6');
            }
            if (n % 2) {
                const int l = n / 2 - 1;
                return string(1, '8') + string(l, '9') + string(1, '8') + string(l, '9') + string(1, '8');
            }
            const int l = n / 2 - 2;
            return string(1, '8') + string(l, '9') + string(2, '7') + string(l, '9') + string(1, '8');
        }
        const int l = n / 12, r = n % 12;
        return string(l * 6, '9') + f(r) + string(l * 6, '9');  // 999999%7 = 0
    }

