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

    int minCostToEqualizeArray(vector<int>& nums, int cost1, int cost2) {
        static const int MOD = 1e9 + 7;

        const int n = size(nums);
        const int64_t mx = ranges::max(nums);
        int64_t total = mx * n - accumulate(cbegin(nums), cend(nums), 0ll);
        // fill until mx with only cost1 operations
        if (n <= 2 || 2 * cost1 <= cost2) {
            return total * cost1 % MOD;
        }

        int64_t result = numeric_limits<int64_t>::max();
        // fill until mx with more cost2 operations and fewer cost1 operations
        const int64_t mn = ranges::min(nums);
        int64_t cnt1 = max((mx - mn) - (total - (mx - mn)), static_cast<int64_t>(0));
        int64_t cnt2 = total - cnt1;
        result = min(result, (cnt1 + cnt2 % 2) * cost1 + cnt2 / 2 * cost2);

        // fill until mx+x with most cost2 operations and fewest cost1 operations,
        // where x is the max of x s.t. cnt1+x >= (n-1)*x => cnt1 >= (n-2)*x
        const int64_t x = cnt1 / (n - 2);
        cnt1 %= n - 2;
        total += n * x;
        cnt2 = total - cnt1;
        result = min(result, (cnt1 + cnt2 % 2) * cost1 + (cnt2 / 2) * cost2);

        // fill until mx+x+1 or mx+x+2 with nearly all cost2 operations and at most one cost1 operation
        for (int _ = 0; _ < 2; ++_) {  // increase twice is for odd n
            total += n;
            result = min(result, total % 2 * cost1 + total / 2 * cost2);
        }
        return result % MOD;
    }

