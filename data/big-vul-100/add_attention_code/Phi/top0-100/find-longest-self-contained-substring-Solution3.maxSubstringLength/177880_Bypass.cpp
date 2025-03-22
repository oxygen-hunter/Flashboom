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

    int maxSubstringLength(string s) {
        vector<int> cnt(26);
        for (const auto& x : s) {
            ++cnt[x - 'a'];
        }
        const auto& update = [&](auto& cnt2, char x, int d, int& distinct, int& valid) {
            const int k = x - 'a';
            if (cnt2[k] == cnt[k]) {
                --valid;
            }
            if (cnt2[k] == 0) {
                ++distinct;
            }
            cnt2[k] += d;
            if (cnt2[k] == 0) {
                --distinct;
            }
            if (cnt2[k] == cnt[k]) {
                ++valid;
            }
         };

        const int total = accumulate(cbegin(cnt), cend(cnt), 0, [](const int accu, const int x) {
            return accu + (x != 0 ? 1 : 0);
        });
        int result = -1;
        for (int l = 1; l < total; ++l) {
            vector<int> cnt2(26);
            for (int right = 0, left = 0, distinct = 0, valid = 0; right < size(s); ++right) {
                update(cnt2, s[right], +1, distinct, valid);
                while (distinct == l + 1) {
                    update(cnt2, s[left++], -1, distinct, valid);
                }
                if (valid == l) {
                    result = max(result, right - left + 1);
                }
            }
        }
        return result;
    }

