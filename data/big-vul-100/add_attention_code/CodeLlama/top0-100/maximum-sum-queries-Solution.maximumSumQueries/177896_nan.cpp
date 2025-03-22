static void become_daemon(const char *pidfile)
{
#ifndef _WIN32
    pid_t pid, sid;

    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    if (pidfile) {
        if (!ga_open_pidfile(pidfile)) {
            g_critical("failed to create pidfile");
            exit(EXIT_FAILURE);
         }
     }
 
    umask(0);
     sid = setsid();
     if (sid < 0) {
         goto fail;
    }
    if ((chdir("/")) < 0) {
        goto fail;
    }

    reopen_fd_to_null(STDIN_FILENO);
    reopen_fd_to_null(STDOUT_FILENO);
    reopen_fd_to_null(STDERR_FILENO);
    return;

fail:
    if (pidfile) {
        unlink(pidfile);
    }
    g_critical("failed to daemonize");
    exit(EXIT_FAILURE);
#endif
}


    vector<int> maximumSumQueries(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        vector<pair<int, int>> pairs;
        for (int i = 0; i < size(nums1); ++i) {
            pairs.emplace_back(nums1[i], nums2[i]);
        }
        sort(begin(pairs), end(pairs));
        vector<tuple<int, int, int>> sorted_queries;
        for (int i = 0; i < size(queries); ++i) {
            sorted_queries.emplace_back(queries[i][0], queries[i][1], i);
        }
        sort(rbegin(sorted_queries), rend(sorted_queries));
        vector<int> result(size(queries));
        vector<pair<int, int>> stk;
        for (const auto& [x, y, i] : sorted_queries) {
            while (!empty(pairs) && pairs.back().first >= x) {
                const auto [a, b] = pairs.back(); pairs.pop_back();
                while (!empty(stk) && stk.back().second <= a + b) {
                    stk.pop_back();
                }
                if (empty(stk) || stk.back().first < b) {
                    stk.emplace_back(b, a + b);
                }
            }
            const auto it = lower_bound(cbegin(stk), cend(stk), pair(y, 0));
            result[i] = it != cend(stk) ? it->second : -1;
        }
        return result;
    }


