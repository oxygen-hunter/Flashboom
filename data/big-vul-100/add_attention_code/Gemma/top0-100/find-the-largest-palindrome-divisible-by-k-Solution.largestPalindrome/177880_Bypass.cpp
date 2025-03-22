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


