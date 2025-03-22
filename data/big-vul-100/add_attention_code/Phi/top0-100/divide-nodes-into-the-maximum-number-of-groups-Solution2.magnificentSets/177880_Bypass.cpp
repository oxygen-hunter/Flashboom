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

    int magnificentSets(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            adj[e[0] - 1].emplace_back(e[1] - 1);
            adj[e[1] - 1].emplace_back(e[0] - 1);
        }
        vector<bool> lookup(n);
        const auto& bfs = [&](int u) {
            vector<int> group = {u};
            vector<int> q = {u};
            lookup[u] = true;
            while (!empty(q)) {
                vector<int> new_q;
                for (const auto& u : q) {
                    group.emplace_back(u);
                    for (const auto& v : adj[u]) {
                        if (lookup[v]) {
                            continue;
                        }
                        lookup[v] = true;
                        new_q.emplace_back(v);
                    }
                }
                q = move(new_q);
            }
            return group;
        };
        const auto& bfs2 = [&](int u) {
            int result = 0;
            vector<bool> lookup(n);
            unordered_set<int> q = {u};
            lookup[u] = true;
            for (; !empty(q); ++result) {
                unordered_set<int> new_q;
                for (const auto& u : q) {
                    for (const auto& v : adj[u]) {
                        if (q.count(v)) {
                            return 0;
                        }
                        if (lookup[v]) {
                            continue;
                        }
                        lookup[v] = true;
                        new_q.emplace(v);
                    }
                }
                q = move(new_q);
            }
            return result;
        };

        int result = 0;
        for (int u = 0; u < n; ++u) {
            if (lookup[u]) {
                continue;
            }
            const auto& group = bfs(u);
            int mx = 0;
            for (const auto& u : group) {
                const int d = bfs2(u);
                if (d == 0) {
                    return -1;
                }
                mx = max(mx, d);
            }
            result += mx;
        }
        return result;
    }

