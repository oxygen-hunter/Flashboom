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


    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        static const int K = 3;

        vector<vector<int>> left{grid}, right{grid};
        for (int i = 1; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]) - 1; ++j) {
                left[i][j] += left[i - 1][j + 1];
            }
        }
        for (int i = 1; i < size(grid); ++i) {
            for (int j = 1; j < size(grid[0]); ++j) {
                right[i][j] += right[i - 1][j - 1];
            }
        }
        priority_queue<int, vector<int>, greater<int>> min_heap;
        unordered_set<int> lookup;
        for (int k = 0; k <= (min(size(grid), size(grid[0])) + 1) / 2; ++k) {
            for (int i = k; i < size(grid) - k; ++i) {
                for (int j = k; j < size(grid[0]) - k; ++j) {
                    int total = k ? ((left[i][j - k] - left[i - k][j]) + (right[i][j + k] - right[i - k][j]) + grid[i - k][j]) +  
                                    ((left[i + k][j] - left[i][j + k]) + (right[i + k][j] - right[i][j - k]) - grid[i + k][j])
                                  : grid[i][j];
                    if (lookup.count(total)) {
                        continue;
                    }
                    lookup.emplace(total);
                    min_heap.emplace(total);
                    if (size(min_heap) == K + 1) {
                        lookup.erase(min_heap.top()); min_heap.pop();
                    }
                }
            }
        }
        vector<int> result;
        while (!empty(min_heap)) {
            result.emplace_back(min_heap.top()); min_heap.pop();
        }
        reverse(begin(result), end(result));
        return result;
    }


