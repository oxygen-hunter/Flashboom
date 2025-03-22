check_file_permissions_reduced(i_ctx_t *i_ctx_p, const char *fname, int len,
                        gx_io_device *iodev, const char *permitgroup)
{
    long i;
    ref *permitlist = NULL;
    /* an empty string (first character == 0) if '\' character is */
    /* recognized as a file name separator as on DOS & Windows    */
    const char *win_sep2 = "\\";
    bool use_windows_pathsep = (gs_file_name_check_separator(win_sep2, 1, win_sep2) == 1);
    uint plen = gp_file_name_parents(fname, len);

     /* we're protecting arbitrary file system accesses, not Postscript device accesses.
      * Although, note that %pipe% is explicitly checked for and disallowed elsewhere
      */
    if (iodev != iodev_default(imemory)) {
         return 0;
     }
 
    /* Assuming a reduced file name. */
    if (dict_find_string(&(i_ctx_p->userparams), permitgroup, &permitlist) <= 0)
        return 0;       /* if Permissions not found, just allow access */

    for (i=0; i<r_size(permitlist); i++) {
        ref permitstring;
        const string_match_params win_filename_params = {
                '*', '?', '\\', true, true      /* ignore case & '/' == '\\' */
        };
        const byte *permstr;
        uint permlen;
        int cwd_len = 0;

        if (array_get(imemory, permitlist, i, &permitstring) < 0 ||
            r_type(&permitstring) != t_string
           )
            break;      /* any problem, just fail */
        permstr = permitstring.value.bytes;
        permlen = r_size(&permitstring);
        /*
         * Check if any file name is permitted with "*".
         */
        if (permlen == 1 && permstr[0] == '*')
            return 0;           /* success */
        /*
         * If the filename starts with parent references,
         * the permission element must start with same number of parent references.
         */
        if (plen != 0 && plen != gp_file_name_parents((const char *)permstr, permlen))
            continue;
        cwd_len = gp_file_name_cwds((const char *)permstr, permlen);
        /*
         * If the permission starts with "./", absolute paths
         * are not permitted.
         */
        if (cwd_len > 0 && gp_file_name_is_absolute(fname, len))
            continue;
        /*
         * If the permission starts with "./", relative paths
         * with no "./" are allowed as well as with "./".
         * 'fname' has no "./" because it is reduced.
         */
        if (string_match( (const unsigned char*) fname, len,
                          permstr + cwd_len, permlen - cwd_len,
                use_windows_pathsep ? &win_filename_params : NULL))
            return 0;           /* success */
    }
    /* not found */
    return gs_error_invalidfileaccess;
}

    int maximumScore(vector<int>& nums, int k) {
        static const int MOD = 1e9 + 7;
        const auto& addmod = [&](uint32_t a, uint32_t b) {  // avoid overflow
            a %= MOD, b %= MOD;
            if (MOD - a <= b) {
                b -= MOD;  // relied on unsigned integer overflow in order to give the expected results
            }
            return a + b;
        };

        const auto& mulmod = [&](uint32_t a, uint32_t b)  {  // avoid overflow
            a %= MOD, b %= MOD;
            uint32_t result = 0;
            if (a < b) {
                swap(a, b);
            }
            while (b > 0)  { 
                if (b % 2 == 1) {
                    result = addmod(result, a);
                }
                a = addmod(a, a);
                b /= 2; 
            } 
            return result; 
        };

        const auto& powmod = [&](uint32_t a, uint32_t b) {
            a %= MOD;
            uint32_t result = 1;
            while (b) {
                if (b & 1) {
                    result = mulmod(result, a);
                }
                a = mulmod(a, a);
                b >>= 1;
            }
            return result;
        };
    
        const auto& linear_sieve_of_eratosthenes = [](int n) {  // Time: O(n), Space: O(n)
            vector<int> spf(n + 1, -1);
            vector<int> primes;
            for (int i = 2; i <= n; ++i) {
                if (spf[i] == -1) {
                    spf[i] = i;
                    primes.emplace_back(i);
                }
                for (const auto& p : primes) {
                    if (i * p > n || p > spf[i]) {
                        break;
                    }
                    spf[i * p] = p;
                }
            }
            return primes;
        };
    
        const auto& primes = linear_sieve_of_eratosthenes(sqrt(*max_element(cbegin(nums), cend(nums))));
        unordered_map<int, int> lookup;
        const auto& count_of_distinct_prime_factors = [&](int x) {
            const int y = x;
            if (!lookup.count(y)) {
                int cnt = 0;
                for (const auto& p : primes) {
                    if (p * p > x) {
                        break;
                    }
                    if (x % p != 0) {
                        continue;
                    }
                    ++cnt;
                    for (; x % p == 0; x /= p);
                }
                if (x != 1) {
                    ++cnt;
                }
                lookup[y] = cnt;
            }
            return lookup[y];
        };

        vector<int> scores;
        scores.reserve(size(nums));
        for (const auto& x : nums) {
            scores.emplace_back(count_of_distinct_prime_factors(x));
        }

        vector<int> stk = {-1};
        vector<int> left(size(scores), -1);
        for (int i = 0; i < size(scores); ++i) {
            while (stk.back() != -1 && scores[stk.back()] < scores[i]) {  // if multiple such elements exist, choose the one with the smallest index
                stk.pop_back();
            }
            left[i] = stk.back();
            stk.emplace_back(i);
        }
        stk = {static_cast<int>(size(scores))};
        vector<int> right(size(scores), -1);
        for (int i =  size(scores) - 1; i >= 0; --i) {
            while (stk.back() != size(scores) && scores[stk.back()] <= scores[i]) {
                stk.pop_back();
            }
            right[i] = stk.back();
            stk.emplace_back(i);
        }

        int result = 1;
        vector<pair<int, int>> pairs;
        pairs.reserve(size(nums));
        for (int i = 0; i < size(nums); ++i) {
            pairs.emplace_back(nums[i], i);
        }
        priority_queue<pair<int, int>> max_heap(cbegin(pairs), cend(pairs));
        while (!empty(max_heap)) {
            const auto [_, i] = max_heap.top(); max_heap.pop();
            const int c = min((i - left[i]) * (right[i] - i), k);
            result = mulmod(result, powmod(nums[i], c));
            k -= c;
            if (!k) {
                break;
            }
        }
        return result;
    }

