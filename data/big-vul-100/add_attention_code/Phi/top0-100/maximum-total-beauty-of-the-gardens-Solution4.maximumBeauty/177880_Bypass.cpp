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

    long long maximumBeauty(vector<int>& flowers, long long newFlowers, int target, int full, int partial) {
        const auto& check = [](const auto& prefix, const auto& total, auto x) {
            return (prefix[x] - prefix[x - 1]) * x - prefix[x] <= total;
        };
        const auto& binary_search_right = [&check](const auto& prefix, const auto& total, auto left, auto right) {
            while (left <= right) {
                const auto mid = left + (right - left) / 2;
                if (!check(prefix, total, mid)) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return right;
        };
        const auto it = partition(begin(flowers), end(flowers), [&target](int x) { return x < target; });
        sort(begin(flowers), it);
        const long long n = distance(begin(flowers), it);
        vector<long long> prefix(n + 1);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + flowers[i];
        }
        long long result = 0, suffix = 0;
        for (long long right = n; right >= 0; --right) {
            if (right != n) {
                suffix += flowers[right];
            }
            const auto total = newFlowers - (static_cast<long long>(n - right) * target - suffix);
            if (total < 0) {
                break;
            }
            const auto left = binary_search_right(prefix, total, 1, right);
            const auto mn = min(left ? (total + prefix[left]) / left : 0ll, static_cast<long long>(target) - 1);
            result = max(result, mn * partial + (static_cast<long long>(size(flowers)) - right) * full);
        }
        return result;
    }

