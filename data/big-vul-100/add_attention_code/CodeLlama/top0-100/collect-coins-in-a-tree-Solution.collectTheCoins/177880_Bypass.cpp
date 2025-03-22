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


    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        static const int DISTANCE = 2;

        vector<unordered_set<int>> adj(size(coins));
        for (const auto& e : edges) {
            adj[e[0]].emplace(e[1]);
            adj[e[1]].emplace(e[0]);
        }
        int n = size(coins);
        for (int i = 0; i < size(coins); ++i) {
            int u = i;
            while (size(adj[u]) == 1 && !coins[u]) {
                const int v = *cbegin(adj[u]);
                adj[u].erase(v);
                adj[v].erase(u);
                --n;
                u = v;
            }
        }
        vector<int> q;
        for (int u = 0; u < size(coins); ++u) {
            if (size(adj[u]) == 1) {
                q.emplace_back(u);
            }
        }
        for (int _ = 0; _ < DISTANCE; ++_) {
            vector<int> new_q;
            for (const auto& u : q) {
                if (empty(adj[u])) {
                    assert(n == 1);
                    break;
                }
                const int v = *cbegin(adj[u]);
                adj[u].erase(v);
                adj[v].erase(u);
                --n;
                if (size(adj[v]) == 1) {
                    new_q.emplace_back(v);
                }
            }
            q = move(new_q);
        }
        return (n - 1) * 2;
    }


