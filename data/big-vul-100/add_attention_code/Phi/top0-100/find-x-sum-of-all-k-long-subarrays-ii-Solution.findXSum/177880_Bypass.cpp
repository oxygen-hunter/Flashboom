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

    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        using ordered_set = tree<pair<int, int64_t>, null_type, greater<pair<int, int64_t>>, rb_tree_tag, tree_order_statistics_node_update>;
        ordered_set os;
        unordered_map<int, int64_t> cnt;
        const auto& update = [&](int v, int64_t d, int64_t curr) {
            if (d == 1) {
                os.insert({cnt[v], v});
            }
            if (os.order_of_key(pair(cnt[v], v)) < x) {
                curr += d * cnt[v] * v;
                if (x < size(os)) {
                    const auto [nc, nv] = *(os.find_by_order(x));
                    curr -= d * nc * nv;
                }
            }
            if (d != 1) {
                os.erase(pair(cnt[v], v));
            }
            return curr;
        };

        vector<long long> result;
        for (int64_t i = 0, curr = 0; i < size(nums); ++i) {
            if (cnt.count(nums[i])) {
                curr = update(nums[i], -1, curr);
            }
            ++cnt[nums[i]];
            curr = update(nums[i], +1, curr);
            if (i < k - 1) {
                continue;
            }
            result.emplace_back(curr);
            curr = update(nums[i - (k - 1)], -1, curr);
            --cnt[nums[i - (k - 1)]];
            if (cnt[nums[i - (k - 1)]]) {
                curr = update(nums[i - (k - 1)], +1, curr);
            } else {
                cnt.erase(nums[i - (k - 1)]);
            }
        }
        return result;
    }

