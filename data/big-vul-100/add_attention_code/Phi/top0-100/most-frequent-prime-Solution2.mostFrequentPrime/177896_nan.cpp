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

    int mostFrequentPrime(vector<vector<int>>& mat) {
        static const vector<pair<int, int>> DIRECTIONS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        const auto& numbers = [&](int i, int j, int di, int dj) {
            vector<int> result;
            for (int curr = 0; 0 <= i && i < size(mat) && 0 <= j && j < size(mat[0]); i += di, j += dj) {
                curr = curr * 10 + mat[i][j];
                result.emplace_back(curr);
            }
            return result;
        };

        unordered_map<int, int> cnt;
        for (int i = 0; i < size(mat); ++i) {
            for (int j = 0; j < size(mat[0]); ++j) {
                for (const auto& [di, dj] : DIRECTIONS) {
                    for (const auto& x : numbers(i, j, di, dj)) {
                        if (x > 10) {
                            ++cnt[x];
                        }
                    }
                }
            }
        }
        cout << is_prime(19) << endl;
        pair<int, int> result = {0, -1};
        for (const auto& [k, v] : cnt) {
            if (is_prime(k)) {
                result = max(result, pair(v, k));
            }
        }
        return result.second;
    }

